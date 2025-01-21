#include "App/AppSettings.h"
#include "stdafx.h"
#include "GolfClub.h"

void GolfClub::Init()
{
    collider.radius = 10;
    strikeCounter = 0;
}

void GolfClub::StrikeBall(GolfBall& ball)
{
    if (canStrike)
    {
        strikeCounter++;
        ApplyEdgeCollisionForce(ball.transform.velocity, ball.transform.position, transform.position, transform.velocity, ball.body.radius, impactMultiplier);
        canStrike = false;
    }
}

void GolfClub::Update()
{
    collider.radius = 10;
    collider.position = transform.position;
    if (!canStrike)
    {
        strikeCooldown--;
        if (strikeCooldown <= 0)
        {
            canStrike = true;
            strikeCooldown = 20;
        }
    }

    previousPos = transform.position;
    float x, y;
    App::GetMousePos(x, y);
    transform.position.Set(x, y);
    UpdateMousePosition(transform.position);
    transform.velocity = CalculateVelocity();

    float dynamicColliderRadius = ball->transform.velocity == Vector2::Zero() ? ball->body.radius + (transform.velocity.GetMagnitude() * 0.3f) : ball->body.radius;
    ball->collider.radius = dynamicColliderRadius;

    if (ball->collider.CollisionDetected(collider))
    {
        StrikeBall(*ball);
    }
}

void GolfClub::Draw()
{
    if (visualDebugOn)
    {
        ShapeRenderer::RenderShapeWithNSides(collider.position.GetX(), collider.position.GetY(), collider.radius, 1, 0, 0, 12, 0);
    }
    App::Print(0, APP_VIRTUAL_HEIGHT - 50, "          Strikes: ", 1, 1, 0);
    App::Print(130, APP_VIRTUAL_HEIGHT - 50, std::to_string(strikeCounter).c_str(), 1, 1, 0);
}

void GolfClub::UpdateMousePosition(Vector2 currentPos)
{
    positionHistory.push_back(transform.position);
    if (positionHistory.size() > smoothingWindow)
    {
        positionHistory.pop_front();
    }
}

Vector2 GolfClub::CalculateVelocity(Vector2& prev, Vector2& cur)
{
    Vector2 delta = cur - prev;
    return delta.GetMagnitude();
}

Vector2 GolfClub::CalculateVelocity()
{
    if (positionHistory.size() < 2) return Vector2(0, 0);

    Vector2 totalDelta(0, 0);
    for (size_t i = 1; i < positionHistory.size(); ++i)
    {
        totalDelta = totalDelta + (positionHistory[i] - positionHistory[i - 1]);
    }

    // Average the movement
    return totalDelta / static_cast<float>(positionHistory.size() - 1);
}

Vector2 GolfClub::GetBallEdgeImpactPoint(const Vector2& ballCenter, const Vector2& cursorPos, float ballRadius)
{
    Vector2 direction = (cursorPos - ballCenter).GetNormalized();
    return ballCenter + direction * ballRadius;
}

void GolfClub::ApplyEdgeCollisionForce(Vector2& ballVelocity, const Vector2& ballCenter, const Vector2& cursorPos, const Vector2& cursorVelocity, float ballRadius, float forceMultiplier)
{
    Vector2 impactPoint = GetBallEdgeImpactPoint(ballCenter, cursorPos, ballRadius);
    Vector2 impactNormal = (impactPoint - ballCenter).GetNormalized();
    float velocityAlongNormal = Vector2::Dot(ballVelocity, impactNormal);
    Vector2 reflection = impactNormal * ballVelocity - 2.0f * velocityAlongNormal;
    Vector2 impactDirection = (cursorPos - impactPoint).GetNormalized();
    float impactMagnitude = Vector2::Dot(cursorVelocity, impactDirection);
    Vector2 additionalForce = impactDirection * impactMagnitude * forceMultiplier;
    ballVelocity = reflection + additionalForce;
}
