#pragma once

#include "game_objects.hpp"
#include "levels.hpp"

#include <vector>
#include <cstdlib>
#include <ctime>

class GameState {
public:

    void loadLevel(Level level)
    {
        _level = std::move(level);

        _pad.x = 0.5f;
        _pad.y = _pad.h / 2.0f;

        _ballIsAttached = true;
    }

    void update(float deltaSec)
    {
        // The ball does not have free movement when attached to the pad.
        if (_ballIsAttached) {
            return;
        }
    }

private:
    Level _level;
    Pad _pad;
    Ball _ball;
    bool _ballIsAttached;
};

