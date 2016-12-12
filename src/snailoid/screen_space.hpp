#pragma once

#include "geometry.hpp"

namespace screen {

typedef int Coord;

typedef geometry::Point<Coord> Point;
typedef geometry::AxisRect<Coord> Rect;
typedef geometry::AxisEllipse<Coord> Ellipse;

} // namespace screen
