#pragma once
#include "Vector2.h"
#include "App/app.h"
namespace Component
{

  class SpriteRenderer
  {
    public:
      std::string file;
      float scale;
      Vector2 position;
      CSimpleSprite* sprite;
      SpriteRenderer(std::string filepath, float s, Vector2 p);
      SpriteRenderer();
      void SetPosition(Vector2 p);
      void SetScale(float s);
      void Draw();
      void Update();
  };
}

