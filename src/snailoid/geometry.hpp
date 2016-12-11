#pragma once

/**
 * Geometry primitives
 */

#include "2dspace.hpp"

#include <vector>

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
    Circle(Scalar x, Scalar y, Scalar radius);

    const Point& center() const { return _center; }
    const Scalar& radius() const { return _radius; }

private:
    Point _center;
    Scalar _radius;
};

class Segment {
public:
    Segment(Point start, Point end);
    Segment(Scalar x1, Scalar y1, Scalar x2, Scalar y2);

    const Point& start() const { return _start; }
    const Point& end() const { return _end; }

private:
    Point _start;
    Point _end;
};

class Corridor {
public:
    Corridor(Point base1, Point base2, Vector direction);
    Corridor(const Point &center, Vector direction, Scalar halfWidth);

    const Point& base1() const { return _base1; }
    const Point& base2() const { return _base2; }
    const Vector& direction() const { return _direction; }

private:
    Point _base1;
    Point _base2;
    Vector _direction;
};

class AxisRect {
public:
    AxisRect(Scalar x, Scalar y, Scalar w, Scalar h);

    std::vector<Segment> segments() const;
    
private:
    Scalar _x;
    Scalar _y;
    Scalar _w;
    Scalar _h; 
};

Scalar distance(const Point& p, const Line& l);
Point lineCross(const Line& l1, const Line& l2);
Point projection(const Point& p, const Line& l);
bool pointsOnSameSideOfLine(const Line& l, const Point& p1, const Point& p2);
bool pointInCorridor(const Point& p, const Corridor& c);
Scalar pointCoordOnLine(const Point& p, const Line& l);
Point linePointAtCoord(const Line& l, Scalar coord);
Line lineOfSegment(const Segment& s);
bool intersect(const Segment& s, const Line& l);
bool intersect(const Segment& s, const Corridor& corridor);