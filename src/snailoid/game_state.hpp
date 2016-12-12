#pragma once

#include "game_objects.hpp"
#include "levels.hpp"

#include <vector>

namespace game {

struct State {
    State();

    void addBlock(float x, float y, float w, float h)
    {
        blocks.emplace_back(x, y, w, h);
    }

    void update(float deltaSec);

    Ball ball;
    std::vector<Block> blocks;
};

} // namespace game