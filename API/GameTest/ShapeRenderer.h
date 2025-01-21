#include "stdafx.h"
#include <cmath>
#include <math.h>
#include "App/app.h"
#include "Vector2.h"
namespace ShapeRenderer
{
  // Renders a regular polygon with any number of sides
static void RenderShapeWithNSides(float cx, float cy, float radius, float r, float g, float b, int numSegments, float rotation)
{
    for (int i = 0; i < numSegments; ++i)
    {
        float angle_1 = 2.0f * PI * static_cast<float>(i) / static_cast<float>(numSegments);
        float angle_2 = 2.0f * PI * static_cast<float>(i + 1) / static_cast<float>(numSegments);

        float x1 = cx + radius * cosf(angle_1 + rotation);
        float y1 = cy + radius * sinf(angle_1 + rotation);
        float x2 = cx + radius * cosf(angle_2 + rotation);
        float y2 = cy + radius * sinf(angle_2 + rotation);

        App::DrawLine(x1, y1, x2, y2, r, g, b);
    }
}
static void RenderBox(float sx, float sy, float width, float height, float r = 1, float g = 1, float b = 1)
{
  App::DrawLine(sx, sy, sx + width, sy, r, g, b);
  App::DrawLine(sx, sy, sx, sy + height, r, g, b);
  App::DrawLine(sx, sy + height, sx + width, sy + height, r, g, b);
  App::DrawLine(sx + width, sy, sx + width, sy + height, r, g, b);
}

static void RenderTriangle(Vector2 p1, Vector2 p2, Vector2 p3, float r = 1, float g = 1, float b = 1)
{
  App::DrawLine(p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY(), r, g, b);
  App::DrawLine(p2.GetX(), p2.GetY(), p3.GetX(), p3.GetY(), r, g, b);
  App::DrawLine(p3.GetX(), p3.GetY(), p1.GetX(), p1.GetY(), r, g, b);
}

}
