#include "App/SimpleSprite.h"
#include "Vector2.h"
#include <string>
#include "app\app.h"
namespace Component
{

  struct Transform
  {
    Vector2 position;
    Vector2 scale = Vector2::One();
  };
  struct Velocity
  {
    Vector2 velocity;
  };
  struct Surface{};

  struct BoxCollider{};
  struct CircleCollider
  {
    Vector2 position;
    float radius;
    bool CollisionDetected(Vector2 &other)
    {
      float distance = Vector2::Distance(position, other);
      return distance <= radius;
    }
bool CollisionDetected(const CircleCollider& other)
    {
        float distance = Vector2::Distance(position, other.position);
        return distance <= (radius + other.radius);
    }
  };
  struct EdgeCollider{};
  struct Friction
  {
    float friction;
  };
  struct Circle
  {
    float radius;
  };


  struct SpriteRenderer
  {

    std::string file;
    float scale;
    Vector2 position;
    CSimpleSprite *sprite;
    SpriteRenderer(std::string filepath, float s, Vector2 p)
    {
      file = filepath;
      scale = s;
      position = p;

      sprite = App::CreateSprite(file.c_str(), 1, 1);
      sprite->SetScale(this->scale);
      sprite->SetPosition(this->position.GetX(), this->position.GetY());
    }
    void SetPosition(Vector2 p)
    {
      position = p;
    }
    void SetScale(float s)
    {
      scale = s;
    }
    SpriteRenderer() {};
    void Draw()
    {
      sprite->Draw();
    }
    void Update()
    {
      sprite->SetPosition(position.GetX(), position.GetY());
    }
  };




}
