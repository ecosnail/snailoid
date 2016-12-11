#include "exceptions.hpp"
#include "frame_timer.hpp"
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

    GameState state;

    View view(configuration.view);
    view.attach(state);
    
    FrameTimer timer(60.f);

    bool done = false;
    while (!done) {
        SDL_Event evt;
        while (SDL_PollEvent(&evt)) {
            switch (evt.type) {
                case SDL_QUIT:
                    done = true;
            }
        }

        if (!timer.itIsTime()) {
            continue;
        }

        view.render();

        state.update(0.01f);
    }


    return 0;
}
