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

CircleCollision circleCollidesSegment(
    const Circle& circle,
    const Vector& direction,
    const Segment& segment);

template <class P>
CircleCollision circleCollidesPolygon(
    const Circle& circle,
    const Vector& direction,
    const P& polygon)
{
    CircleCollision closestCollision = CircleCollision::none;
    Scalar closestDistance = std::numeric_limits<float>::infinity();
    for (const Segment& s : polygon.segments()) {
        CircleCollision collision = circleCollidesSegment(circle, direction, s);
        if (collision.happened) {
            Scalar dist = distance(circle.center(), collision.circleCenter);
            if (dist < closestDistance) {
                closestDistance = dist;
                closestCollision = collision;
            }
        }
    }

    return closestCollision;
}