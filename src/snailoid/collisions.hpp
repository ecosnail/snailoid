#pragma once

#include "geometry.hpp"


class CircleCollision {
public:
    CircleCollision(Point circleCenter, Point collisionPoint);

    static const CircleCollision none;

    bool happened;
    Point circleCenter;
    Point collisionPoint;

private:
    CircleCollision();
};

CircleCollision circleCollidesLine(
    const Circle& circle,
    const Vector& direction,
    const Line& line);

CircleCollision circleCollidesPoint(
    const Circle& circle,
    const Vector& direction,
    const Point& point);
