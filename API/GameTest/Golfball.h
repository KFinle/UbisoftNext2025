#pragma once
#include "App/AppSettings.h"
#include "App/app.h"
#include "Components.h"
#include "ShapeRenderer.h"
struct GolfBall
{
  bool visualDebugOn = true;
  Component::CircleCollider collider;
  Component::Friction friction;
  Component::Velocity velocity;
  Component::Transform transform;
  Component::Circle body;
  Component::SpriteRenderer sprite;
  GolfBall()
  {
    friction.friction = 0.98f;
    body.radius = 15;
    collider.radius = 15;
  }

  void Update()
  {
    KeepWithinScreenBoundaries();
    transform.position += velocity.velocity;
    velocity.velocity *= friction.friction;
    collider.position = transform.position;
    sprite.SetPosition(transform.position);
    sprite.Update();
  }

  void KeepWithinScreenBoundaries()
  {
    if (transform.position.GetX() > APP_VIRTUAL_WIDTH )
    {
      velocity.velocity.SetX(velocity.velocity.GetX() * -1);
    

    }
    if (transform.position.GetX() < 0)
    {
      velocity.velocity.SetX(velocity.velocity.GetX() * -1);

    }
    if (transform.position.GetY() > APP_VIRTUAL_HEIGHT)
    {
      velocity.velocity.SetY(velocity.velocity.GetY() * -1);

    }
    if (transform.position.GetY() < 0)
    {
      velocity.velocity.SetY(velocity.velocity.GetY() * -1);

    }
  }

  void Draw()
  {
    sprite.Draw();
    if (visualDebugOn)
    {
      DrawRadius();
      DrawCollision();
    }
  }


  void DrawRadius()
  {
    ShapeRenderer::RenderShapeWithNSides(collider.position.GetX(), collider.position.GetY(), collider.radius, 1, 0, 1, 12, 0);
  }

  void DrawCollision()
  {
    
    float mousex, mousey;
    App::GetMousePos(mousex, mousey);
    Vector2 mousePos = Vector2(mousex,mousey);
    if (collider.CollisionDetected(mousePos))
    {
      App::DrawLine(transform.position.GetX() - body.radius, transform.position.GetY() - body.radius, transform.position.GetX() + body.radius, transform.position.GetY() + body.radius, 1, 0,0);
      App::DrawLine(transform.position.GetX() + body.radius, transform.position.GetY() - body.radius, transform.position.GetX() - body.radius, transform.position.GetY() + body.radius, 1, 0,0);
    }
  }
};

