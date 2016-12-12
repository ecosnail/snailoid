#include "exceptions.hpp"
#include "timer.hpp"
#include "game_state.hpp"

#include "configuration.hpp"
#include "sdl_libs.hpp"
#include "view.hpp"

#include <fstream>
#include <iostream>
#include <array>

namespace cfg = ecosnail::config;

int main(int argc, char *argv[])
{
    Configuration configuration;

    std::ifstream configFile("snailoid.cfg");
    cfg::read(configuration, configFile);
    configFile.close();

    game::State state;

    View view(configuration.view);

    view.setViewport(Viewport::simple2d(
        game::AxisRect(0, 0, 1, 1),
        screen::Rect(0, 0, configuration.view.screen_width, configuration.view.screen_height)));

    view.attach(state);

    FrameTimer timer(configuration.gameplay.fps);
    bool done = false;
    while (!done) {
        SDL_Event evt;
        while (SDL_PollEvent(&evt)) {
            switch (evt.type) {
                case SDL_QUIT:
                    done = true;
            }
        }

        if (timer.itIsTime()) {
            state.update(timer.timePerFrame());
            view.render();
        }
    }

    return 0;
}
