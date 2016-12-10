#pragma once

#include "geometry.hpp"

struct CircleCollision {
    CircleCollision(Point circleCenter, Point collisionPoint);

    Point circleCenter;
    Point collisionPoint;
};

CircleCollision circleCollidesLine(
    const Circle& circle,
    const Vector& direction,
    const Line& line);
