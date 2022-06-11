/*
The MIT License (MIT)

Copyright (c) 2021-2022 Filippo Alberto Munaro

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include "MathUtils.h"

#include <math.h>

namespace Shard2D
{
    float MathUtils::Clamp(float value, float min, float max)
    {
        if (value > max)
            return max;
        else if (value < min)
            return min;
        else
            return value;
    }

    float MathUtils::Clamp01(float value)
    {
        return Clamp(value, 0, 1);
    }

    float MathUtils::RoundToZero(float value)
    {
        if (value > 0)
            if (value < 0.0001)
                return 0;
            else
                return value;
        else
            if (value > -0.0001)
                return 0;
            else
                return value;
    }

    float MathUtils::Distance(const Vector2& a, const Vector2& b)
    {
        float distX = abs(a.x - b.x);
        float disty = abs(a.y - b.y);
        return sqrt(distX * distX + disty * disty);
    }

    Vector2 MathUtils::PositionFromRad(float rotation)
    {
        float x = cos(rotation);
        float y = sin(rotation);
        return Vector2(RoundToZero(x), RoundToZero(y));
    }

    Vector2 MathUtils::PositionFromDeg(float rotation)
    {
        float radRotation = rotation * 2 * M_PI / 360;
        return PositionFromRad(radRotation);
    }

    float MathUtils::DegFromPosition(Vector2 position, Vector2 centre)
    {
        Vector2 normalizedPosition = (position - centre).SquareNormalize();
        float rotation = (normalizedPosition.x * -1 + 1) / 2 * 180;
        if (normalizedPosition.y < 0)
            rotation = 360 - rotation;
        return rotation;
    }

    void MathUtils::GenerateRect(Vector2* rectPoints, Vector2 origin, float width, float height, float rotation, bool centerPivot)
    {
        if (!centerPivot)
        {
            rectPoints[0] = origin;
            rectPoints[1] = origin + (PositionFromDeg(rotation) * width);
            rectPoints[3] = origin + (PositionFromDeg(rotation + 90) * height);
            rectPoints[2] = origin + (rectPoints[1] - origin) + (rectPoints[3] - origin);
        }
        else
        {
            origin.x += width / 2;
            origin.y += height / 2;

            rectPoints[0] = origin + (PositionFromDeg(rotation) * (width / 2)) + (PositionFromDeg(rotation + 270) * (height / 2));
            rectPoints[1] = origin + (PositionFromDeg(rotation + 180) * (width / 2)) + (PositionFromDeg(rotation + 270) * (height / 2));
            rectPoints[3] = origin + (PositionFromDeg(rotation) * (width / 2)) + (PositionFromDeg(rotation + 90) * (height / 2));
            rectPoints[2] = origin + (PositionFromDeg(rotation + 180) * (width / 2)) + (PositionFromDeg(rotation + 90) * (height / 2));
        }
    }

    bool MathUtils::PointInsideRect(Vector2 point, Vector2 origin, float width, float height, float rotation, bool centerPivot)
    {
        Vector2 rectPoints[4];

        GenerateRect(rectPoints, origin, width, height, rotation, centerPivot);

        int i, j, c = 0;
        for (i = 0, j = 4 - 1; i < 4; j = i++) {
            if (((rectPoints[i].y > point.y) != (rectPoints[j].y > point.y)) &&
                (point.x < (rectPoints[j].x - rectPoints[i].x) * (point.y - rectPoints[i].y) / (rectPoints[j].y - rectPoints[i].y) + rectPoints[i].x))
                c = ~c;
        }
        return c;
    }
}
