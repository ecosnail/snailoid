#pragma once

#include "game_space.hpp"

#include <utility>

namespace game {

struct Block {
    Block(float x, float y, float w, float h)
        : geometry(x, y, w, h)
    { }

    AxisRect geometry;
};

//struct Cell {
//public:
//    Cell() : _hasBlock(false), _block() {}
//
//    Cell(Block block)
//        : _hasBlock(true)
//        , _block(std::move(block))
//    { }
//
//    static Cell empty()
//    {
//        return Cell();
//    }
//
//    bool hasBlock() const { return _hasBlock; }
//
//private:
//    bool _hasBlock;
//    Block _block;
//};

struct Pad {
    float x;
    float y;
    float vx;
    float vy;
    float w;
    float h;
};

struct Ball {
    Ball()
        : geometry(0.5f, 0.1f, 0.05f)
        , velocity(0.1f, 0.1f)
    { }

    Circle geometry;
    Vector velocity;
};

} // namespace game