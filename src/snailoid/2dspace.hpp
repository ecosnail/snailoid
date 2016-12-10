#pragma once

typedef float Scalar;

/**
 * Vector in 2D game space.
 *
 * Vectors support basic arithmetic operations.
 *
 * Right-handed orientation is assumed for operations that depend on it. That
 * is:
 * * Y axis unit vector is X axis unit vector turned 90 degrees CCW
 * * X, Y, Z base is right-handed (which is important for cross product)
 */
class Vector {
public:
    static const Vector zero;

    Vector(Scalar x, Scalar y) : _x(x), _y(y) {}
    Vector(const Vector& other) : _x(other._x), _y(other._y) {}

    Scalar x() const { return _x; }
    Scalar y() const { return _y; }
    
    Vector operator-() const;

    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    Vector& operator*=(const Scalar& scalar);
    Vector& operator/=(const Scalar& scalar);

    friend Vector operator+(Vector lhs, const Vector& rhs);
    friend Vector operator-(Vector lhs, const Vector& rhs);
    friend Vector operator*(Vector lhs, const Scalar& scalar);
    friend Vector operator*(const Scalar& scalar, Vector rhs);
    friend Vector operator/(Vector lhs, const Scalar& scalar);

private:
    Scalar _x;
    Scalar _y;
};

/** Vector length */
Scalar len(const Vector& v);

/** Square of vector length */
Scalar sqrlen(const Vector& v);

/** Vector turned 90 degrees CCW */
Vector ccw90(const Vector& v);

/** Vector turned 90 degrees CW */
Vector cw90(const Vector& v);

/** Dot product of two vectors */
Scalar dot(const Vector& v1, const Vector& v2);

/** Z coordinate of cross product of two vectors */
Scalar cross(const Vector& v1, const Vector& v2);

/** Normalized vector */
Vector normalized(const Vector& v);

/**
 * Point in 2D game space.
 */
class Point {
public:
    static const Point zero;

    Point(Scalar x, Scalar y) : _x(x), _y(y) {}
    Point(const Point& other) : _x(other._x), _y(other._y) {}

    Point& operator+=(const Vector& v);
    Point& operator-=(const Vector& v);

    friend Point operator+(Point p, const Vector& v);
    friend Point operator-(Point p, const Vector& v);

    Scalar x() const { return _x; }
    Scalar y() const { return _y; }

private:
    Scalar _x;
    Scalar _y;
};

/** Vector v, such that p1 + v = p2 */
Vector operator-(Point p2, const Point &p1);

/** Distance between 2 points */
Scalar distance(const Point& p1, const Point& p2);

/** Coordinate of point p along axis vector v */
Scalar coordAlong(const Point& p, const Vector& v);
