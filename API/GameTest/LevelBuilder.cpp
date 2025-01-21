#include "stdafx.h"
#include "Collider.h"
#include <ctime>
#include <string>
#include "LevelBuilder.h"
#include "App/AppSettings.h"

namespace LevelBuilder
{
  int Level::currentLevel = 1;
    Level::Level() {}


    Level::Level(const Vector2& spawn, const GameObject& goalObject)
    {
        this->spawnPoint = spawn;
        this->goalPoint = goalObject;
    }

    void Level::AddObject(GameObject& object)
    {
        levelObjects.push_back(object);
    }

    void Level::DrawObjects()
    {
      App::Print(0, APP_VIRTUAL_HEIGHT - 20, "Current Level: ", 1,1,0);
      App::Print(130, APP_VIRTUAL_HEIGHT - 20, std::to_string(currentLevel).c_str(), 1,1,0);
        for (GameObject obj : levelObjects)
        {
          if (obj.type == ShapeType::GOAL)
          {
              if (Component::CircleCollider* circle = dynamic_cast<Component::CircleCollider*>(obj.collider))
              {
                  circle->DrawGoal();
              }
          }
          else 
          {
              obj.collider->Draw();
          }
        }
    }

    bool Level::IsOverlapping(Component::Collider* newCollider)
    {
        for (const GameObject& obj : levelObjects)
        {

            if (obj.collider->CollisionDetected(*newCollider))
            {
                return true;
            }
        }
        return false;
    }

    Level Level::GenerateLevel(int numObjects)
    {
        const float minGap = 50.0f;
        std::srand(std::time(nullptr));

        // Spawn point
        Vector2 spawnPoint(std::rand() % APP_VIRTUAL_WIDTH, std::rand() % (APP_VIRTUAL_HEIGHT/5) + 10);
        Component::CircleCollider* spawnPointCollider = new Component::CircleCollider(spawnPoint, 50);
        GameObject spawn(ShapeType::NONE, spawnPointCollider);

        // Goal object
        Vector2 goalPosition(std::rand() % APP_VIRTUAL_WIDTH, std::rand() % APP_VIRTUAL_HEIGHT/2 + 300);
        float goalRadius = 30.0f;

        Component::CircleCollider* goalCollider = new Component::CircleCollider(goalPosition, goalRadius, true);
        GameObject goal(ShapeType::GOAL, goalCollider);

        Level level(spawnPoint, goal);
        level.AddObject(goal);

        // Random shapes
        for (int i = 0; i < numObjects; i++ )
        {
            ShapeType type = static_cast<ShapeType>(std::rand() % 2);
            Component::Collider* collider = nullptr;
            GameObject newObject;

            switch (type)
            {
                case ShapeType::BOX:
                {
                    Vector2 position(std::rand() % APP_VIRTUAL_WIDTH, std::rand() % APP_VIRTUAL_HEIGHT);
                    Vector2 dimensions(std::rand() % 100 + 30 , std::rand() % 100 + 30);
                    collider = new Component::BoxCollider(position, dimensions);
                    newObject = GameObject(type, collider);
                    break;
                }
                case ShapeType::CIRCLE:
                {
                    Vector2 position(std::rand() % APP_VIRTUAL_WIDTH, std::rand() % APP_VIRTUAL_HEIGHT);
                    float radius = std::rand() % 100 + 30;
                    collider = new Component::CircleCollider(position, radius);
                    newObject = GameObject(type, collider);
                    break;
                }
                default:
                    break;
            }
            // Ensure no overlap with existing objects + maintain minimum gap
            bool hasSufficientGap = true;
            for (const GameObject& obj : level.levelObjects)
            {
                float distance = Vector2::Distance(obj.collider->position, collider->position);
                float combinedRadii = obj.collider->GetBoundingRadius() + collider->GetBoundingRadius() + minGap;

                if (distance < combinedRadii)
                {
                    hasSufficientGap = false;
                    break;
                }
            }

            if (hasSufficientGap && !level.IsOverlapping(collider) && !collider->CollisionDetected(*spawnPointCollider))
            {
                level.AddObject(newObject);
            }
            else
            {
                delete collider;
                collider = nullptr;
            };
        }

        delete spawnPointCollider;
        return level;
    }
}
