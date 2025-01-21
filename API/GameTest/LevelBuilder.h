#pragma once
#include "Vector2.h"
#include "Collider.h"
#include "App/app.h"
#include <vector>
enum ShapeType
{
    BOX,
    CIRCLE,
    GOAL,
    NONE
};

struct Box
{
    float x, y, width, height;
    /*Component::BoxCollider collider;*/
};
struct Circle
{
    float centerX, centerY, radius;
    Component::CircleCollider collider;
};

struct GameObject
{
    Component::Collider *collider = nullptr;
    ShapeType type = NONE;
    GameObject(){}

    GameObject(ShapeType type, Component::Collider *collider)
    {
        this->type = type;
        this->collider = collider;
    }
    void AddCollider(Component::Collider *collider)
    {
        this->collider = collider;
    }
    Component::Collider* GetCollider()
    {
        return collider;
    }
};

namespace LevelBuilder
{
    class Level
    {
    public:
        Level(const Vector2& spawn, const GameObject& goalObject);
        Level();
        static int currentLevel;
        void DrawObjects();
        bool IsOverlapping(Component::Collider* newCollider);
        void AddObject(GameObject& object);
        static Level GenerateLevel(int numObjects);
        Vector2 spawnPoint;
        GameObject goalPoint;
        std::vector<GameObject> levelObjects;
    };
}
