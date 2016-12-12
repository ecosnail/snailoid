#pragma once

#include "geometry.hpp"

namespace game {

typedef float Coord;

typedef geometry::Point<Coord> Point;
typedef geometry::Circle<Coord> Circle;
typedef geometry::Vector<Coord> Vector;
typedef geometry::Line<Coord> Line;
typedef geometry::Segment<Coord> Segment;
typedef geometry::AxisRect<Coord> AxisRect;
typedef geometry::Corridor<Coord> Corridor;

} // namespace game