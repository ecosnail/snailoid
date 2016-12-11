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

Circle::Circle(Scalar x, Scalar y, Scalar radius)
    : _center(x, y)
    , _radius(radius)
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

bool pointInCorridor(const Point& p, const Corridor& c)
{
    Line l1 = Line::directed(c.base1(), c.direction());
    Line l2 = Line::directed(c.base2(), c.direction());
    return pointsOnSameSideOfLine(l1, c.base2(), p) &&
        pointsOnSameSideOfLine(l2, c.base1(), p);
}

Point linePointAtCoord(const Line& l, Scalar coord)
{
    return l.base() + coord * l.direction();
}

Segment::Segment(Point start, Point end)
    : _start(std::move(start))
    , _end(std::move(end))
{ }

Segment::Segment(Scalar x1, Scalar y1, Scalar x2, Scalar y2)
    : _start(x1, y1)
    , _end(x2, y2)
{ }

Corridor::Corridor(Point base1, Point base2, Vector direction)
    : _base1(std::move(base1))
    , _base2(std::move(base2))
    , _direction(std::move(direction))
{ }

Corridor::Corridor(const Point &center, Vector direction, Scalar halfWidth)
    : _direction(std::move(direction))
    , _base1(Point::zero)
    , _base2(Point::zero)
{
    Vector offsetVector = halfWidth * normalized(ccw90(direction));
    _base1 = center + offsetVector;
    _base2 = center - offsetVector;
}

Line lineOfSegment(const Segment& s)
{
    return Line::directed(s.start(), s.end() - s.start());
}

bool intersect(const Segment& s, const Line& l)
{
    Line segmentLine = lineOfSegment(s);
    Point x = lineCross(segmentLine, l);
    Scalar xCoord = pointCoordOnLine(x, segmentLine);
    return xCoord >= 0 && xCoord <= 1;
}

bool intersect(const Segment& s, const Corridor& corridor)
{
    Line l1 = Line::directed(corridor.base1(), corridor.direction());
    Line l2 = Line::directed(corridor.base2(), corridor.direction());
    return intersect(s, l1) || intersect(s, l2);
}

AxisRect::AxisRect(Scalar x, Scalar y, Scalar w, Scalar h)
    : _x(x), _y(y), _w(w), _h(h)
{ }

std::vector<Segment> AxisRect::segments() const
{
    return {
        { _x     , _y     , _x + _w, _y      },
        { _x + _w, _y     , _x + _w, _y + _h },
        { _x + _w, _y + _h, _x     , _y + _h },
        { _x     , _y + _h, _x     , _y      },
    };
}
