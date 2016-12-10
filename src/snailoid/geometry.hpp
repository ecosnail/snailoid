#pragma once

/**
 * Geometry primitives
 */

#include "2dspace.hpp"

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
    Circle(Point center, Scalar radius);

    const Point& center() const { return _center; }
    const Scalar& radius() const { return _radius; }

private:
    Point _center;
    Scalar _radius;
};

Scalar distance(const Point& p, const Line& l);
Point lineCross(const Line& l1, const Line& l2);
Point projection(const Point& p, const Line& l);
bool pointsOnSameSideOfLine(const Line& l, const Point& p1, const Point& p2);
bool pointBetweenLines(const Point& p, const Line& l1, const Line& l2);
Scalar pointCoordOnLine(const Point& p, const Line& l);
Point linePointAtCoord(const Line& l, Scalar coord);
