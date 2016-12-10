#pragma once

/**
 * Basic geometry functions.
 *
 * Defined for a 2D space with right (x, y) base.
 */

typedef float Coord;

class Vector {
public:
    Vector(Coord x, Coord y) : _x(x), _y(y) {}
    Vector(const Vector& other) : _x(other._x), _y(other._y) {}

    Coord x() const { return _x; }
    Coord y() const { return _y; }

    static Vector zero() { return Vector(0, 0); }
    
    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    Vector& operator*=(const Coord& scalar);
    Vector& operator/=(const Coord& scalar);

    friend Vector operator+(Vector lhs, const Vector& rhs);
    friend Vector operator-(Vector lhs, const Vector& rhs);
    friend Vector operator*(Vector lhs, const Coord& scalar);
    friend Vector operator*(const Coord& scalar, Vector rhs);
    friend Vector operator/(Vector lhs, const Coord& scalar);

    Vector operator-() const;

private:
    Coord _x;
    Coord _y;
};

class Point {
public:
    static const Point zero;

    Point(Coord x, Coord y) : _x(x), _y(y) {}
    Point(const Point& other) : _x(other._x), _y(other._y) {}

    Point& operator+=(const Vector& v);
    Point& operator-=(const Vector& v);

    friend Point operator+(Point p, const Vector& v);
    friend Point operator-(Point p, const Vector& v);

    Coord x() const { return _x; }
    Coord y() const { return _y; }

private:
    Coord _x;
    Coord _y;
};

class Line {
public:
    static Line directed(Point basePoint, Vector direction);
    static Line withNorm(Point basePoint, Vector norm);

    const Point& base() const { return _basePoint; }
    const Vector& direction() const { return _direction; }
    const Vector& norm() const { return _norm; }

private:
    Line(Point basePoint, Vector direction, Vector norm);

    Point _basePoint;
    Vector _direction;
    Vector _norm;
};

class Circle {
public:
    Circle(Point center, Coord radius);

    const Point& center() const { return _center; }
    const Coord& radius() const { return _radius; }

private:
    Point _center;
    Coord _radius;
};

Vector operator-(Point lhs, const Point &rhs);

Coord len(const Vector& v);
Coord sqrlen(const Vector& v);

Coord dot(const Vector& v1, const Vector& v2);
Coord cross(const Vector& v1, const Vector& v2);

Coord distance(const Point& p1, const Point& p2);
Coord distance(const Point& p, const Line& l);

Coord coordAlong(const Point& p, const Vector& v);

Point lineCross(const Line& l1, const Line& l2);

Vector normalized(const Vector& v);

Point projection(const Point& p, const Line& l);
