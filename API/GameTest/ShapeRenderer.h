#include "stdafx.h"
#include <cmath>
#include <math.h>
#include "App/app.h"
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

}
