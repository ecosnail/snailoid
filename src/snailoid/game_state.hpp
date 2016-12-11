#pragma once

#include "game_objects.hpp"
#include "levels.hpp"

#include <vector>

class GameState {
public:
    void addBlock(float x, float y, float w, float h)
    {
        _blocks.emplace_back(x, y, w, h);
    }

    void update(float deltaSec);

//private:
    Ball _ball;
    std::vector<Block> _blocks;
};

