/* Component.h */
#pragma once
#include "Vector2.h"
#include <string>


namespace Component
{
    struct Transform
    {
        Vector2 position;
        Vector2 scale = Vector2::One();
        Vector2 velocity;
    };

    struct Surface {};


    struct EdgeCollider {};

    struct Friction
    {
        float friction;
    };

    struct Circle
    {
        float radius;
    };


}
