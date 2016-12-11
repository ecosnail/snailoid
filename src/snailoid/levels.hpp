#pragma once

#include "game_objects.hpp"

#include <array>
#include <vector>

//struct Level {
//public:
//    static constexpr size_t width = 16;
//    static constexpr size_t height = 12;
//    static constexpr size_t cellCount = width * height;
//
//    Level(
//        const std::vector<Cell>& cellTypes,
//        const std::array<size_t, cellCount>& field)
//    {
//        for (size_t i = 0; i < cellCount; i++) {
//            _cells[i] = cellTypes[field[i]];
//        }
//    }
//
//private:
//    std::array<Cell, width * height> _cells;
//};

//Level level0 = {
//    {
//        Cell::empty(),
//        Block(),
//    },
//    {
//        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//        0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
//        0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
//        0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
//        0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
//        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
//        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    }
//};
