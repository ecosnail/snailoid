#pragma once

#include <algorithm>

template <class T>
T clamp(T value, const T& min, const T& max)
{
    return std::min(std::max(value, min), max);
}

namespace geometry {

/**
 * Vector in 2D space.
 *
 * Vectors support basic arithmetic operations.
 *
 * Right-handed orientation is assumed for operations that depend on it. That
 * is:
 * * Y axis unit vector is X axis unit vector turned 90 degrees CCW
 * * X, Y, Z base is right-handed (which is important for cross product)
 */
template <class T>
class Vector {
public:
    static const Vector zero;

    Vector(T x, T y) : _x(x), _y(y) {}
    Vector(const Vector& other) : _x(other._x), _y(other._y) {}

    T x() const { return _x; }
    T y() const { return _y; }
    
    Vector operator-() const { return Vector(-x(), -y()); };
 
    Vector& operator+=(const Vector& other)
    {
        _x += other._x;
        _y += other._y;
        return *this;
    }

    Vector& operator-=(const Vector& other)
    {
        _x -= other._x;
        _y -= other._y;
        return *this;
    }

    Vector& operator*=(const T& scalar)
    {
        _x *= scalar;
        _y *= scalar;
        return *this;
    }

    Vector& operator/=(const T& scalar)
    {
        _x /= scalar;
        _y /= scalar;
        return *this;
    }

private:
    T _x;
    T _y;
};

template <class T>
const Vector<T> Vector<T>::zero(0, 0);

template <class T>
Vector<T> operator+(Vector<T> lhs, const Vector<T>& rhs)
{
    lhs += rhs;
    return lhs;
}

template <class T>
Vector<T> operator-(Vector<T> lhs, const Vector<T>& rhs)
{
    lhs -= rhs;
    return lhs;
}

template <class T>
Vector<T> operator*(Vector<T> lhs, const T& scalar)
{
    lhs *= scalar;
    return lhs;
}

template <class T>
Vector<T> operator*(const T& scalar, Vector<T> rhs)
{
    rhs *= scalar;
    return rhs;
}

template <class T>
Vector<T> operator/(Vector<T> lhs, const T& scalar)
{
    lhs /= scalar;
    return lhs;
}

/** Vector length */
template <class T>
T len(const Vector<T>& v)
{
    return std::sqrt(sqrlen(v));
}

/** Square of vector length */
template <class T>
T sqrlen(const Vector<T>& v)
{
    return v.x() * v.x() + v.y() * v.y();
}

/** Vector turned 90 degrees CCW */
template <class T>
Vector<T> ccw90(const Vector<T>& v)
{
    return Vector<T>(-v.y(), v.x());
}

/** Vector turned 90 degrees CW */
template <class T>
Vector<T> cw90(const Vector<T>& v)
{
    return Vector(v.y(), -v.x());
}

/** Dot product of two vectors */
template <class T>
T dot(const Vector<T>& v1, const Vector<T>& v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y();
}

/** Z coordinate of cross product of two vectors */
template <class T>
T cross(const Vector<T>& v1, const Vector<T>& v2)
{
    return v1.x() * v2.y() - v1.y() * v2.x();
}

/** Normalized vector */
template <class T>
Vector<T> normalized(const Vector<T>& v)
{
    return v / len(v);
}

/** Projection of vector v onto line base */
template <class T>
Vector<T> projection(
    const Vector<T>& v,
    const Vector<T>& direction)
{
    Vector<T> axis = normalized(direction);
    T coord = dot<T>(v, axis);
    return axis * coord;
}

/** Ort of vector v projected onto direction */
template <class T>
Vector<T> ort(const Vector<T>& v, const Vector<T>& direction)
{
    return v - projection(v, direction);
}

template <class T>
Vector<T> mirrorBy(const Vector<T>& v, const Vector<T>& mirror)
{
    return v - 2 * ort(v, mirror);
}

template <class T>
Vector<T> mirrorAlong(
    const Vector<T>& v,
    const Vector<T>& direction)
{
    return v - T(2) * projection(v, direction);
}

/**
 * Point in 2D space.
 */
template <class T>
class Point {
public:
    static const Point zero;

    Point(T x, T y) : _x(x), _y(y) {}
    Point(const Point& other) : _x(other._x), _y(other._y) {}

    Point& operator+=(const Vector<T>& v)
    {
        _x += v.x();
        _y += v.y();
        return *this;
    }

    Point& operator-=(const Vector<T>& v)
    {
        _x -= v.x();
        _y -= v.y();
        return *this;
    }

    const T& x() const { return _x; }
    const T& y() const { return _y; }

private:
    T _x;
    T _y;
};

template <class T>
const Point<T> Point<T>::zero(0, 0);

template <class T>
Point<T> operator+(Point<T> p, const Vector<T>& v)
{
    p += v;
    return p;
}

template <class T>
Point<T> operator-(Point<T> p, const Vector<T>& v)
{
    p -= v;
    return p;
}

template <class T>
Vector<T> operator-(Point<T> lhs, const Point<T> &rhs)
{
    return Vector<T>(
        lhs.x() - rhs.x(), 
        lhs.y() - rhs.y());
}

/** Distance between 2 points */
template <class T>
T distance(const Point<T>& p1, const Point<T>& p2)
{
    return len(p2 - p1);
}

/** Coordinate of point p along axis vector v */
template <class T>
T coordAlong(const Point<T>& p, const Vector<T>& v)
{
    return dot<T>(normalized(v), p - Point<T>::zero);
}

} // namespace geometry
