#include "stdafx.h"
#include "Golfball.h"
#include "Collider.h"
#include "GolfMath.h"
namespace Component
{
    // CircleCollider Implementation
    CircleCollider::CircleCollider(Vector2& position, float radius, bool isTrigger)
        : radius(radius)
    {
        this->position = position;
        this->isTrigger = isTrigger;
    }

    CircleCollider::CircleCollider() : radius(0) {}

    // CircleCollider
    bool CircleCollider::CollisionDetected(Collider& other) {
        return other.CollisionDetected(*this); // Delegate to specific type
    }

    float CircleCollider::GetBoundingRadius()
    {
        return radius;
    }

    bool CircleCollider::CollisionDetected(CircleCollider& other) {
        float distance = Vector2::Distance(position, other.position);
        return distance <= (radius + other.radius);
    }

    bool CircleCollider::CollisionDetected(BoxCollider& box) {
        return box.CollisionDetected(*this); // Use BoxCollider's logic
    }

    void CircleCollider::Draw()
    {
      ShapeRenderer::RenderShapeWithNSides(position.GetX(), position.GetY(), radius, 0, 0.5f, 1, 36, 0);
    }
    void CircleCollider::DrawGoal()
    {
        ShapeRenderer::RenderShapeWithNSides(position.GetX(), position.GetY(), radius, 0, 1, 0, 36, 0);
    }


    // BoxCollider Implementation
    BoxCollider::BoxCollider(Vector2& position, Vector2& dimensions)
        : dimensions(dimensions) 
    {
        this->position = position;
    }

    bool BoxCollider::CollisionDetected(Collider& other) {
        return other.CollisionDetected(*this);
    }
    bool BoxCollider::CollisionDetected(CircleCollider& circle)
    {
        float closestX = GolfMath::Max(position.GetX(), GolfMath::Min(circle.position.GetX(), position.GetX() + dimensions.GetX()));
        float closestY = GolfMath::Max(position.GetY(), GolfMath::Min(circle.position.GetY(), position.GetY() + dimensions.GetY()));
        float distance = Vector2::Distance(circle.position, Vector2(closestX, closestY));
        return distance <= circle.radius;
    }

bool BoxCollider::CollisionDetected(BoxCollider& other) {
    return !(position.GetX() + dimensions.GetX() < other.position.GetX() ||  // Fully to the left
             position.GetX() > other.position.GetX() + other.dimensions.GetX() ||  // Fully to the right
             position.GetY() + dimensions.GetY() < other.position.GetY() ||  // Fully above
             position.GetY() > other.position.GetY() + other.dimensions.GetY()); // Fully below
}
float BoxCollider::GetBoundingRadius()
{
    return 0.5f * sqrt(dimensions.GetX() * dimensions.GetX() + dimensions.GetY() * dimensions.GetY());
}
    void BoxCollider::Draw()
    {
      ShapeRenderer::RenderBox(position.GetX(), position.GetY(), dimensions.GetX(), dimensions.GetY(), 0.3f, 0.9f, 1);
    }
    void Collider::Draw()
    {
    }
}
