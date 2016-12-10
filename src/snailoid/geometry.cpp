#include "geometry.hpp"

#include <cmath>
#include <cassert>
#include <utility>

Line::Line(Point basePoint, Vector direction, Vector norm)
    : _basePoint(std::move(basePoint))
    , _direction(std::move(direction))
    , _norm(std::move(norm))
{ }

Line Line::directed(Point basePoint, Vector direction)
{
    return Line(
        basePoint,
        direction,
        normalized(ccw90(direction)));
}

Line Line::withNorm(Point basePoint, Vector norm)
{
    Vector trueNorm = normalized(norm);
    return Line(basePoint, cw90(trueNorm), trueNorm);
}

Scalar distance(const Point& p, const Line& l)
{
    Vector v1 = l.base() - p;
    Vector v2 = v1 + l.direction();
    Scalar triangleSpace = cross(v1, v2) / 2;
    Scalar distance = triangleSpace / len(l.direction());
    return distance;
}

Point lineCross(const Line& l1, const Line& l2)
{
    Scalar divider = std::abs(cross(l1.norm(), l2.norm()));
    Vector n1 = l1.norm();
    Vector n2 = l2.norm();

    Scalar c1 = coordAlong(l1.base(), n1);
    Scalar c2 = coordAlong(l2.base(), n2);
    Scalar xBase = c1 * n2.y() - c2 * n1.y();
    Scalar yBase = n1.x() * c2 - n2.x() * c1;

    return Point(xBase / divider, yBase / divider);
}

Circle::Circle(Point center, Scalar radius)
    : _center(std::move(center))
    , _radius(std::move(radius))
{ }

Scalar pointCoordOnLine(const Point& p, const Line& l)
{
    Scalar pCoord = coordAlong(p, l.direction());
    Scalar baseCoord = coordAlong(l.base(), l.direction());
    return pCoord - baseCoord;
}

Point projection(const Point& p, const Line& l)
{
    return linePointAtCoord(l, pointCoordOnLine(p, l));
}

bool pointsOnSameSideOfLine(const Line& l, const Point& p1, const Point& p2)
{
    Point lp1 = l.base();
    Point lp2 = lp1 + l.direction();

    return cross(lp1 - p1, lp2 - p1) * cross(lp1 - p2, lp2 - p2) > 0;
}

bool pointBetweenLines(const Point& p, const Line& l1, const Line& l2)
{
    return pointsOnSameSideOfLine(l1, l2.base(), p) &&
        pointsOnSameSideOfLine(l2, l1.base(), p);
}

Point linePointAtCoord(const Line& l, Scalar coord)
{
    return l.base() + coord * l.direction();
}
