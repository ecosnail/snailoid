#pragma once

#include <utility>

struct Block {
    Block() { }
};

struct Cell {
public:
    Cell() : _hasBlock(false), _block() {}

    Cell(Block block)
        : _hasBlock(true)
        , _block(std::move(block))
    { }

    static Cell empty()
    {
        return Cell();
    }

    bool hasBlock() const { return _hasBlock; }

private:
    bool _hasBlock;
    Block _block;
};

struct Pad {
    float x;
    float y;
    float vx;
    float vy;
    float w;
    float h;
};

struct Ball {
    float x;
    float y;
    float radius;
    float vx;
    float vy;
};
