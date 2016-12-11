#pragma once

#include <ecosnail/config.hpp>
#include <string>

struct Configuration {
    struct View {
        std::string title;
        int screen_width;
        int screen_height;
        float fps;

        DEFINE_FIELDS(title, screen_width, screen_height, fps)
    };

    View view;

    DEFINE_FIELDS(view)
};
