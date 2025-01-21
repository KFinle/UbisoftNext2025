#include "stdafx.h"
#include "Golfball.h"
#include "GolfMath.h"

GolfBall::GolfBall()
{
    friction.friction = 0.98f;
    body.radius = 22;
    collider.radius = 22;
}

void GolfBall::Update()
{
    KeepWithinScreenBoundaries();
    HandleLevelCollision(level);
    transform.position += transform.velocity;
    transform.velocity *= friction.friction;
    collider.position = transform.position;
    sprite.SetPosition(transform.position);
    sprite.Update();

    trailPositions.push_back(transform.position);

    if (trailPositions.size() > maxTrailSize) {
        trailPositions.pop_front();
    }
}

void GolfBall::KeepWithinScreenBoundaries()
{
    if (transform.position.GetX() >= APP_VIRTUAL_WIDTH)
    {
        transform.position.SetX(APP_VIRTUAL_WIDTH);
        transform.velocity.SetX(transform.velocity.GetX() * -2);

    }
    if (transform.position.GetX() <= 0)
    {
        transform.position.SetX(0);
        transform.velocity.SetX(transform.velocity.GetX() * -2);

    }
    if (transform.position.GetY() >= APP_VIRTUAL_HEIGHT)
    {
        transform.position.SetY(APP_VIRTUAL_HEIGHT);
        transform.velocity.SetY(transform.velocity.GetY() * -2);

    }
    if (transform.position.GetY() <= 0)
    {
        transform.position.SetY(0);
        transform.velocity.SetY(transform.velocity.GetY() * -2);
    }
    if (transform.velocity.GetX() > maxVelocity) transform.velocity.SetX(maxVelocity);
    if (transform.velocity.GetX() < -maxVelocity) transform.velocity.SetX(-maxVelocity);
    if (transform.velocity.GetY() > maxVelocity) transform.velocity.SetY(maxVelocity);
    if (transform.velocity.GetX() < -maxVelocity) transform.velocity.SetY(-maxVelocity);
}

void GolfBall::Draw()
{
    
    for (int i = 0; i < trailPositions.size(); i++) {
        float alpha = 1.0f - (i * trailFade);
        alpha = GolfMath::Max(alpha, 0.0f);

        float sizeFactor = 1.0f - (static_cast<float>(trailPositions.size() - 1 - i) / trailPositions.size());
        float size = body.radius * (0.2f + sizeFactor * 0.5f);
        size = GolfMath::Max(size, body.radius * 0.1f);
        ShapeRenderer::RenderShapeWithNSides(trailPositions[i].GetX(), trailPositions[i].GetY(), size, 1.0f - alpha, 1.0f - alpha, 1.0f - alpha, 24, 0);
    }



    sprite.Draw();
    if (visualDebugOn)
    {
        DrawRadius();
        DrawCollision();
    }
}


void GolfBall::DrawRadius()
{
    ShapeRenderer::RenderShapeWithNSides(collider.position.GetX(), collider.position.GetY(), collider.radius, 1, 1, 1, 24, 0);
}

void GolfBall::HandleLevelCollision(LevelBuilder::Level& level)
{
    for (int i = 0; i < level.levelObjects.size(); i++)
    {
        if (level.levelObjects[i].collider->CollisionDetected(collider))
        {
            if (level.levelObjects[i].type == ShapeType::GOAL)
            {
                goalFound = true;
            }
            else
            {
                HandleCollision(level.levelObjects[i].collider);
            }

        }

    }


}


void GolfBall::HandleCollision(Component::Collider* other)
{
    if (Component::CircleCollider* circle = dynamic_cast<Component::CircleCollider*>(other)) {
        ReflectCircleCollision(*circle);
    }
    else if (Component::BoxCollider* box = dynamic_cast<Component::BoxCollider*>(other)) {
        ReflectBoxCollision(*box);
    }
}

void GolfBall::ReflectCircleCollision(Component::CircleCollider& other)
{
    Vector2 collisionNormal = transform.position - other.position;
    collisionNormal.Normalize(); // Ensure it's a unit vector
    transform.velocity = transform.velocity - (collisionNormal * Vector2::Dot(transform.velocity, collisionNormal) * 2);
}

void GolfBall::ReflectBoxCollision(Component::BoxCollider& other)
{
    Vector2 closestPoint = GetClosestPointOnBox(other);
    Vector2 collisionNormal = transform.position - closestPoint;
    collisionNormal.Normalize();
    transform.velocity = transform.velocity - (collisionNormal * Vector2::Dot(transform.velocity, collisionNormal) * 2);
}




Vector2 GolfBall::GetClosestPointOnBox(Component::BoxCollider& box)
{
    float closestX = GolfMath::Max(box.position.GetX(), GolfMath::Min(transform.position.GetX(), box.position.GetX() + box.dimensions.GetX()));
    float closestY = GolfMath::Max(box.position.GetY(), GolfMath::Min(transform.position.GetY(), box.position.GetY() + box.dimensions.GetY()));
    return Vector2(closestX, closestY);
}
void GolfBall::DrawCollision()
{
    float mousex, mousey;
    App::GetMousePos(mousex, mousey);
    Vector2 mousePos = Vector2(mousex, mousey);
}
