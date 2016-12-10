#include "geometry.hpp"

#include <cmath>
#include <cassert>
#include <utility>

const Point Point::zero(0, 0);

Point& Point::operator+=(const Vector& v)
{
    _x += v.x();
    _y += v.y();
    return *this;
}

Point& Point::operator-=(const Vector& v)
{
    _x -= v.x();
    _y -= v.y();
    return *this;
}

Point operator+(Point p, const Vector& v) { p += v; return p; }
Point operator-(Point p, const Vector& v) { p -= v; return p; }

Vector Vector::operator-() const
{
    return Vector(-x(), -y());
}

Vector& Vector::operator+=(const Vector& other)
{
    _x += other._x;
    _y += other._y;
    return *this;
}

Vector& Vector::operator-=(const Vector& other)
{
    _x -= other._x;
    _y -= other._y;
    return *this;
}

Vector& Vector::operator*=(const Coord& scalar)
{
    _x *= scalar;
    _y *= scalar;
    return *this;
}

Vector& Vector::operator/=(const Coord& scalar)
{
    _x /= scalar;
    _y /= scalar;
    return *this;
}

Vector operator+(Vector lhs, const Vector& rhs)   { lhs += rhs; return lhs; }
Vector operator-(Vector lhs, const Vector& rhs)   { lhs -= rhs; return lhs; }
Vector operator*(Vector lhs, const Coord& scalar) { lhs *= scalar; return lhs; }
Vector operator*(const Coord& scalar, Vector rhs) { rhs *= scalar; return rhs; }
Vector operator/(Vector lhs, const Coord& scalar) { lhs /= scalar; return lhs; }


Coord len(const Vector& v)
{
    return std::sqrt(sqrlen(v));
}

Coord sqrlen(const Vector& v)
{
    return v.x() * v.x() + v.y() * v.y();
}

Vector operator-(Point lhs, const Point &rhs)
{
    return Vector(
        lhs.x() - rhs.x(), 
        lhs.y() - rhs.y());
}

Coord dot(const Vector& v1, const Vector& v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y();
}

Coord cross(const Vector& v1, const Vector& v2)
{
    return v1.x() * v2.y() - v1.y() * v2.x();
}

Vector ccw90(const Vector& v)
{
    return Vector(-v.y(), v.x());
}

Vector cw90(const Vector& v)
{
    return Vector(v.y(), -v.x());
}

Vector normalized(const Vector& v)
{
    return v / len(v);
}

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

Coord distance(const Point& p1, const Point& p2)
{
    return len(p2 - p1);
}

Coord distance(const Point& p, const Line& l)
{
    Vector v1 = l.base() - p;
    Vector v2 = v1 + l.direction();
    Coord triangleSpace = cross(v1, v2) / 2;
    Coord distance = triangleSpace / len(l.direction());
    return distance;
}

Coord coordAlong(const Point& p, const Vector& v)
{
    return dot(normalized(v), p - Point::zero);
}

Point lineCross(const Line& l1, const Line& l2)
{
    Coord divider = std::abs(cross(l1.norm(), l2.norm()));
    Vector n1 = l1.norm();
    Vector n2 = l2.norm();

    Coord c1 = coordAlong(l1.base(), n1);
    Coord c2 = coordAlong(l2.base(), n2);
    Coord xBase = c1 * n2.y() - c2 * n1.y();
    Coord yBase = n1.x() * c2 - n2.x() * c1;

    return Point(xBase / divider, yBase / divider);
}

Circle::Circle(Point center, Coord radius)
    : _center(std::move(center))
    , _radius(std::move(radius))
{ }

Point projection(const Point& p, const Line& l)
{
    Coord pCoord = coordAlong(p, l.direction());
    Coord baseCoord = coordAlong(l.base(), l.direction());
    Coord delta = pCoord - baseCoord;
    Point target = l.base() + delta * l.direction();
    return target;
}
