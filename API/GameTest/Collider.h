#pragma once
#include "Vector2.h"

namespace Component
{
    class CircleCollider; // forward declaration to ensure base collider can look for circle colliders 
    class TriangleCollider;
    class BoxCollider;

    class Collider
    {
    public:
        bool isTrigger = false;
        Vector2 position;
        virtual bool CollisionDetected(CircleCollider& circle) { return false; }
        virtual bool CollisionDetected(BoxCollider& box) { return false; }
        virtual bool CollisionDetected(Collider& other) = 0;
        virtual float GetBoundingRadius() = 0;
        virtual ~Collider() = default;
        virtual void Draw();
    };

    class CircleCollider : public Collider
    {
    public:
        //Vector2 position;
        float radius;
        CircleCollider(Vector2& position, float radius, bool isTrigger = false);
        CircleCollider();
        bool CollisionDetected(CircleCollider& circle) override;
        bool CollisionDetected(BoxCollider& box) override;
        bool CollisionDetected(Collider& other) override;
        float GetBoundingRadius() override;
        void Draw() override;
        void DrawGoal();
    };
    class BoxCollider : public Collider
    {
    public:
        //Vector2 position;
        Vector2 dimensions;
        BoxCollider(Vector2& position, Vector2& dimensions);
        BoxCollider();
        bool CollisionDetected(Collider& other) override;
        bool CollisionDetected(CircleCollider& circle) override;
        bool CollisionDetected(BoxCollider& box) override;
        float GetBoundingRadius() override;
        void Draw() override;
    };
}
