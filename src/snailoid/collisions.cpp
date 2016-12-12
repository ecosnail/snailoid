#include "collisions.hpp"

#include <utility>
#include <cmath>

namespace game {

const CircleCollision CircleCollision::none;

CircleCollision::CircleCollision()
    : happened(false)
    , circleCenter(Point::zero)
    , collisionPoint(Point::zero)
{ }

CircleCollision::CircleCollision(Point circleCenter, Point collisionPoint)
    : happened(true)
    , circleCenter(std::move(circleCenter))
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

CircleCollision circleCollidesPoint(
    const Circle& circle,
    const Vector& direction,
    const Point& point)
{
    Line movementLine = Line::directed(circle.center(), direction);
    Coord c = pointCoordOnLine(point, movementLine);
    if (c < 0) {
        return CircleCollision::none;
    }

    Point proj = linePointAtCoord(movementLine, c);
    Coord dist = len(proj - point);
    if (dist > circle.radius()) {
        return CircleCollision::none;
    }

    Coord offset = std::sqrt(circle.radius() * circle.radius() - dist * dist);
    Point newCenter = proj - normalized(direction) * offset;

    return CircleCollision(newCenter, point);
}

CircleCollision circleCollidesSegment(
    const Circle& circle,
    const Vector& direction,
    const Segment& segment)
{
    Corridor movementCorridor(circle.center(), direction, circle.radius());
    if (!intersect(segment, movementCorridor)) {
        return CircleCollision::none;
    }

    Line segmentLine = Line::directed(
        segment.start(),
        segment.end() - segment.start());

    CircleCollision lineCollision = circleCollidesLine(
        circle, direction, segmentLine);

    Coord collisionCoord =
        pointCoordOnLine(lineCollision.collisionPoint, segmentLine);
    if (collisionCoord >= 0 && collisionCoord <= 1) {
        return lineCollision;
    }

    Coord fixedCoord = clamp<Coord>(collisionCoord, 0, 1);
    return circleCollidesPoint(
        circle, direction, linePointAtCoord(segmentLine, fixedCoord));
}

} // namespace game