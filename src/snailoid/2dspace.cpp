#include "2dspace.hpp"

#include <cmath>
#include <algorithm>

Scalar clamp(Scalar value, const Scalar& min, const Scalar& max)
{
    return std::min(std::max(value, min), max);
}

/*
 * Vector operations
 */

const Vector Vector::zero(0, 0);

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

Vector& Vector::operator*=(const Scalar& scalar)
{
    _x *= scalar;
    _y *= scalar;
    return *this;
}

Vector& Vector::operator/=(const Scalar& scalar)
{
    _x /= scalar;
    _y /= scalar;
    return *this;
}

Vector operator+(Vector lhs, const Vector& rhs)   { lhs += rhs; return lhs; }
Vector operator-(Vector lhs, const Vector& rhs)   { lhs -= rhs; return lhs; }
Vector operator*(Vector lhs, const Scalar& scalar) { lhs *= scalar; return lhs; }
Vector operator*(const Scalar& scalar, Vector rhs) { rhs *= scalar; return rhs; }
Vector operator/(Vector lhs, const Scalar& scalar) { lhs /= scalar; return lhs; }

Scalar len(const Vector& v)
{
    return std::sqrt(sqrlen(v));
}

Scalar sqrlen(const Vector& v)
{
    return v.x() * v.x() + v.y() * v.y();
}

Scalar dot(const Vector& v1, const Vector& v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y();
}

Scalar cross(const Vector& v1, const Vector& v2)
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

Vector projection(const Vector& v, const Vector& direction)
{
    Vector axis = normalized(direction);
    Scalar coord = dot(v, axis);
    return axis * coord;
}

Vector ort(const Vector& v, const Vector& direction)
{
    return v - projection(v, direction);
}

Vector mirrorBy(const Vector& v, const Vector& mirror)
{
    return v - 2 * ort(v, mirror);
}

Vector mirrorAlong(const Vector& v, const Vector& direction)
{
    return v - 2 * projection(v, direction);
}

/*
 * Point operations
 */

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

Vector operator-(Point lhs, const Point &rhs)
{
    return Vector(
        lhs.x() - rhs.x(), 
        lhs.y() - rhs.y());
}

Scalar distance(const Point& p1, const Point& p2)
{
    return len(p2 - p1);
}

Scalar coordAlong(const Point& p, const Vector& v)
{
    return dot(normalized(v), p - Point::zero);
}

