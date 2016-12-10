#include "collisions.hpp"

#include <utility>

CircleCollision::CircleCollision(Point circleCenter, Point collisionPoint)
    : circleCenter(std::move(circleCenter))
    , collisionPoint(std::move(collisionPoint))
{ }

CircleCollision circleCollidesLine(
    const Circle& circle, 
    const Vector& direction,
    const Line& line)
{
    Coord d = distance(circle.center(), line);
    Line circleMoveLine = Line::directed(circle.center(), direction);

    Point x = lineCross(circleMoveLine, line);
    Coord distanceToCross = len(x - circle.center());

    Coord coeff = len(x - circle.center()) / d;
    Coord offset = circle.radius() * coeff;

    Point newCenter = circle.center() +
        normalized(direction) * (distanceToCross - offset);
    Point collisionPoint = projection(newCenter, line);

    return CircleCollision(newCenter, collisionPoint);
}
