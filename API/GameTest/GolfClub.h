#pragma once
#include "App/app.h"
/*#include "Components.h"*/
#include "Golfball.h"
#include "Vector2.h"
#include <string>
#include <deque>

struct GolfClub
{
  std::deque<Vector2> positionHistory;
  const int smoothingWindow = 5;

  Component::Velocity velocity;
  Component::Transform transform;
  Component::CircleCollider collider;
  Vector2 previousPos;
  GolfBall* ball = nullptr;
  bool visualDebugOn = true;
  bool canStrike = true;
  float strikeCooldown = 5;
  float impactMultiplier = 0.5f;

  void init()
  {
    collider.radius = 10;
  }



  void StrikeBall(GolfBall &ball)
  {
    if (canStrike)
    {
    ApplyEdgeCollisionForce(ball.velocity.velocity, ball.transform.position, transform.position, velocity.velocity, ball.body.radius, impactMultiplier);
    canStrike = false;
    }
  }


  void Update()
  {
    collider.radius = 10;
    collider.position = transform.position;
    if (!canStrike)
    {
      strikeCooldown--;
      if (strikeCooldown <= 0)
      {
        canStrike = true;
        strikeCooldown = 5;
      }
    }
    previousPos = transform.position;
    float x, y;
    App::GetMousePos(x, y);
    transform.position.Set(x, y);
    UpdateMousePosition(transform.position);
    velocity.velocity = CalculateVelocity();


    float dynamicColliderRadius = ball->body.radius + (velocity.velocity.GetMagnitude() * 0.2f);
    ball->collider.radius = dynamicColliderRadius;
    
    if (ball->collider.CollisionDetected(collider))
    {
      StrikeBall(*ball);
    }
  }

  void Draw()
  {
    if (visualDebugOn)
    {
    if (ball->collider.CollisionDetected(collider))
    {
    }
    ShapeRenderer::RenderShapeWithNSides(collider.position.GetX(), collider.position.GetY(), collider.radius, 1, 0, 0, 12, 0);
    }

  }

  void UpdateMousePosition(Vector2 currentPos)
  {
    positionHistory.push_back(transform.position);
    if (positionHistory.size() > smoothingWindow)
    {
      positionHistory.pop_front();
    }
  }

  Vector2 CalculateVelocity(Vector2 &prev, Vector2 &cur)
  {
    Vector2 delta = cur - prev;
    return delta.GetMagnitude();
  }

Vector2 CalculateVelocity() {
    if (positionHistory.size() < 2) return Vector2(0, 0);

    Vector2 totalDelta(0, 0);
    for (size_t i = 1; i < positionHistory.size(); ++i) {
        totalDelta = totalDelta + (positionHistory[i] - positionHistory[i - 1]);
    }

    // Average the movement
    return totalDelta / static_cast<float>(positionHistory.size() - 1);
}


Vector2 GetBallEdgeImpactPoint(const Vector2& ballCenter, const Vector2& cursorPos, float ballRadius) 
{
    Vector2 direction = (cursorPos - ballCenter).GetNormalized();
    return ballCenter + direction * ballRadius;
}

void ApplyEdgeCollisionForce(Vector2& ballVelocity, const Vector2& ballCenter, const Vector2& cursorPos, const Vector2& cursorVelocity, float ballRadius, float forceMultiplier) {
    Vector2 impactPoint = GetBallEdgeImpactPoint(ballCenter, cursorPos, ballRadius);
    Vector2 impactNormal = (impactPoint - ballCenter).GetNormalized();
    float velocityAlongNormal = Vector2::Dot(ballVelocity, impactNormal);
    Vector2 reflection = impactNormal * ballVelocity - 2.0f * velocityAlongNormal;
    Vector2 impactDirection = (cursorPos - impactPoint).GetNormalized();
    float impactMagnitude = Vector2::Dot(cursorVelocity, impactDirection);
    Vector2 additionalForce = impactDirection * impactMagnitude * forceMultiplier;
    ballVelocity = reflection + additionalForce;
}


};


