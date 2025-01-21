#include "stdafx.h"
#include "SpriteRenderer.h"
namespace Component
{


    // SpriteRenderer Implementation
    SpriteRenderer::SpriteRenderer(std::string filepath, float s, Vector2 p)
        : file(filepath), scale(s), position(p)
    {
        sprite = App::CreateSprite(file.c_str(), 1, 1);
        sprite->SetScale(this->scale);
        sprite->SetPosition(this->position.GetX(), this->position.GetY());
    }

    SpriteRenderer::SpriteRenderer() : sprite(nullptr), scale(1.0f), position(Vector2::Zero()) {}

    void SpriteRenderer::SetPosition(Vector2 p)
    {
        position = p;
    }

    void SpriteRenderer::SetScale(float s)
    {
        scale = s;
    }

    void SpriteRenderer::Draw()
    {
        if (sprite)
            sprite->Draw();
    }

    void SpriteRenderer::Update()
    {
        if (sprite)
            sprite->SetPosition(position.GetX(), position.GetY());
    }
};