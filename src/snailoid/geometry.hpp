#pragma once

/**
 * Geometry primitives
 */

#include "2dspace.hpp"

#include <vector>
#include <utility>

namespace geometry {

/**
 * Infinite line.
 */
template <class T>
class Line {
public:
    static Line directed(Point<T> basePoint, Vector<T> direction);
    static Line withNorm(Point<T> basePoint, Vector<T> norm);

    const Point<T>& base() const { return _basePoint; }
    const Vector<T>& direction() const { return _direction; }
    const Vector<T>& norm() const { return _norm; }

private:
    Line(
        Point<T> basePoint,
        Vector<T> direction,
        Vector<T> norm);

    Point<T> _basePoint;
    Vector<T> _direction;
    Vector<T> _norm;
};

template <class T>
Line<T>::Line(
        Point<T> basePoint,
        Vector<T> direction,
        Vector<T> norm)
    : _basePoint(std::move(basePoint))
    , _direction(std::move(direction))
    , _norm(std::move(norm))
{ }

template <class T>
Line<T> Line<T>::directed(
    Point<T> basePoint,
    Vector<T> direction)
{
    return Line<T>(
        basePoint,
        direction,
        normalized(ccw90(direction)));
}

template <class T>
Line<T> Line<T>::withNorm(
    Point<T> basePoint,
    Vector<T> norm)
{
    Vector<T> trueNorm = normalized(norm);
    return Line<T>(basePoint<T>, cw90(trueNorm), trueNorm);
}

/**
 * Circle.
 */
template <class T>
class Circle {
public:
    Circle(Point<T> center, T radius);
    Circle(T x, T y, T radius);

    const Point<T>& center() const { return _center; }
    const T& radius() const { return _radius; }

private:
    Point<T> _center;
    T _radius;
};

template <class T>
Circle<T>::Circle(Point<T> center, T radius)
    : _center(std::move(center))
    , _radius(std::move(radius))
{ }

template <class T>
Circle<T>::Circle(T x, T y, T radius)
    : _center(x, y)
    , _radius(radius)
{ }

/**
 * Segment connecting two points in space.
 */
template <class T>
class Segment {
public:
    Segment(Point<T> start, Point<T> end);
    Segment(T x1, T y1, T x2, T y2);

    const Point<T>& start() const { return _start; }
    const Point<T>& end() const { return _end; }

private:
    Point<T> _start;
    Point<T> _end;
};

template <class T>
Segment<T>::Segment(Point<T> start, Point<T> end)
    : _start(std::move(start))
    , _end(std::move(end))
{ }

template <class T>
Segment<T>::Segment(T x1, T y1, T x2, T y2)
    : _start(x1, y1)
    , _end(x2, y2)
{ }

/**
 * Area bounded by 2 parallel lines.
 */
template <class T>
class Corridor {
public:
    Corridor(
        Point<T> base1,
        Point<T> base2,
        Vector<T> direction);

    Corridor(
        const Point<T> &center,
        Vector<T> direction,
        T halfWidth);

    const Point<T>& base1() const { return _base1; }
    const Point<T>& base2() const { return _base2; }
    const Vector<T>& direction() const { return _direction; }

private:
    Point<T> _base1;
    Point<T> _base2;
    Vector<T> _direction;
};

template <class T>
Corridor<T>::Corridor(
        Point<T> base1,
        Point<T> base2,
        Vector<T> direction)
    : _base1(std::move(base1))
    , _base2(std::move(base2))
    , _direction(std::move(direction))
{ }

template <class T>
Corridor<T>::Corridor(const Point<T> &center,
        Vector<T> direction,
        T halfWidth)
    : _direction(std::move(direction))
    , _base1(Point<T>::zero)
    , _base2(Point<T>::zero)
{
    Vector<T> offsetVector = halfWidth * normalized(ccw90(direction));
    _base1 = center + offsetVector;
    _base2 = center - offsetVector;
}

/**
 * Rectangle with segments parallel to axes.
 */
template <class T>
class AxisRect {
public:
    AxisRect(T x, T y, T w, T h);
    AxisRect(Point<T> p0, Point<T> p1);

    const T& xStart() const { return _x; }
    const T& yStart() const { return _y; }
    T xEnd() const { return _x + _w; }
    T yEnd() const { return _y + _h; }
    Point<T> start() const { return Point<T>(_x, _y); }
    Point<T> end() const { return Point<T>(_x + _w, _y + _h); }
    const T& w() const { return _w; }
    const T& h() const { return _h; }

    std::vector<Segment<T>> segments() const;
    
private:
    T _x;
    T _y;
    T _w;
    T _h; 
};

template <class T>
AxisRect<T>::AxisRect(T x, T y, T w, T h)
    : _x(x), _y(y), _w(w), _h(h)
{ }

template <class T>
AxisRect<T>::AxisRect(Point<T> p0, Point<T> p1)
    : _x(std::min(p0.x(), p1.x()))
    , _y(std::min(p0.y(), p1.y()))
    , _w(std::abs(p0.x() - p1.x()))
    , _h(std::abs(p0.y() - p1.y()))
{ }

template <class T>
std::vector<Segment<T>> AxisRect<T>::segments() const
{
    return {
        { _x     , _y     , _x + _w, _y      },
        { _x + _w, _y     , _x + _w, _y + _h },
        { _x + _w, _y + _h, _x     , _y + _h },
        { _x     , _y + _h, _x     , _y      },
    };
}

template <class T>
class AxisEllipse {
public:
    AxisEllipse(Point<T> center, T rx, T ry);
    AxisEllipse(T x, T y, T rx, T ry);

    const Point<T>& center() const { return _center; }
    const T& x() const { return _center.x(); }
    const T& y() const { return _center.y(); }
    const T& rx() const { return _rx; }
    const T& ry() const { return _ry; }

private:
    Point<T> _center;
    T _rx;
    T _ry;
};

template <class T>
AxisEllipse<T>::AxisEllipse(Point<T> center, T rx, T ry)
    : _center(std::move(center))
    , _rx(std::move(rx))
    , _ry(std::move(ry))
{ }

template <class T>
AxisEllipse<T>::AxisEllipse(T x, T y, T rx, T ry)
    : _center(std::move(x), std::move(y))
    , _rx(std::move(rx))
    , _ry(std::move(ry))
{ }

// Various functions on geometry primitives

template <class T>
T distance(const Point<T>& p, const Line<T>& l)
{
    Vector<T> v1 = l.base() - p;
    Vector<T> v2 = v1 + l.direction();
    T triangleSpace = cross(v1, v2) / 2;
    T distance = triangleSpace / len(l.direction());
    return distance;
}

template <class T>
Point<T> lineCross(const Line<T>& l1, const Line<T>& l2)
{
    T divider = std::abs(cross(l1.norm(), l2.norm()));
    Vector<T> n1 = l1.norm();
    Vector<T> n2 = l2.norm();

    T c1 = coordAlong(l1.base(), n1);
    T c2 = coordAlong(l2.base(), n2);
    T xBase = c1 * n2.y() - c2 * n1.y();
    T yBase = n1.x() * c2 - n2.x() * c1;

    return Point<T>(xBase / divider, yBase / divider);
}

template <class T>
T pointCoordOnLine(const Point<T>& p, const Line<T>& l)
{
    T pCoord = coordAlong(p, l.direction());
    T baseCoord = coordAlong(l.base(), l.direction());
    return pCoord - baseCoord;
}

template <class T>
Point<T> projection(const Point<T>& p, const Line<T>& l)
{
    return linePointAtCoord(l, pointCoordOnLine(p, l));
}

template <class T>
bool pointsOnSameSideOfLine(
    const Line<T>& l,
    const Point<T>& p1,
    const Point<T>& p2)
{
    Point<T> lp1 = l.base();
    Point<T> lp2 = lp1 + l.direction();

    return cross(lp1 - p1, lp2 - p1) * cross(lp1 - p2, lp2 - p2) > 0;
}

template <class T>
bool pointInCorridor(const Point<T>& p, const Corridor<T>& c)
{
    Line<T> l1 = Line<T>::directed(c.base1(), c.direction());
    Line<T> l2 = Line<T>::directed(c.base2(), c.direction());
    return pointsOnSameSideOfLine(l1, c.base2(), p) &&
        pointsOnSameSideOfLine(l2, c.base1(), p);
}

template <class T>
Point<T> linePointAtCoord(const Line<T>& l, T coord)
{
    return l.base() + coord * l.direction();
}


template <class T>
Line<T> lineOfSegment(const Segment<T>& s)
{
    return Line<T>::directed(s.start(), s.end() - s.start());
}

template <class T>
bool intersect(const Segment<T>& s, const Line<T>& l)
{
    Line<T> segmentLine = lineOfSegment<T>(s);
    Point<T> x = lineCross(segmentLine, l);
    T xCoord = pointCoordOnLine<T>(x, segmentLine);
    return xCoord >= 0 && xCoord <= 1;
}

template <class T>
bool intersect(const Segment<T>& s, const Corridor<T>& corridor)
{
    Line<T> l1 =
        Line<T>::directed(corridor.base1(), corridor.direction());
    Line<T> l2 =
        Line<T>::directed(corridor.base2(), corridor.direction());
    return intersect(s, l1) || intersect(s, l2);
}

} // namespace geometry
