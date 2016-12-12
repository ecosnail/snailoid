#pragma once

#include <ecosnail/config.hpp>
#include <string>

struct Configuration {
    struct Gameplay {
        float fps;

        DEFINE_FIELDS(fps)
    };

    struct View {
        std::string title;
        int screen_width;
        int screen_height;

        DEFINE_FIELDS(title, screen_width, screen_height)
    };

    Gameplay gameplay;
    View view;

    DEFINE_FIELDS(gameplay, view)
};
