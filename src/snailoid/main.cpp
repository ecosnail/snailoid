#include "exceptions.hpp"
#include "frame_timer.hpp"
#include "game_state.hpp"

#include <ecosnail/config.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <fstream>
#include <iostream>
#include <array>

namespace cfg = ecosnail::config;

//const std::map<Color, SDL_Color> colorMapping {
//    { Color::BLACK,   { 0,   0,   0,   255 } },
//    { Color::BLUE,    { 0,   0,   255, 255 } },
//    { Color::GREEN,   { 0,   255, 0,   255 } },
//    { Color::YELLOW,  { 0,   255, 255, 255 } },
//    { Color::RED,     { 255, 0,   0,   255 } },
//    { Color::CYAN,    { 255, 0,   255, 255 } },
//    { Color::MAGENTA, { 255, 255, 0,   255 } },
//    { Color::WHITE,   { 255, 255, 255, 255 } },
//};


struct Configuration {
    std::string title;
    int screen_width;
    int screen_height;
    float fps;

    DEFINE_FIELDS(
        title, screen_width, screen_height, fps)
};



int main()
{
    Configuration config;

    std::ifstream configFile("snailoid.cfg");
    cfg::read(config, configFile);
    configFile.close();

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        THROW(SdlException);
    }
    
    SDL_Window *window = SDL_CreateWindow(
        config.title.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        config.screen_width,
        config.screen_height,
        SDL_WINDOW_SHOWN);
    if (!window) {
        THROW(SdlException);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        THROW(SdlException);
    }

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


        SDL_RenderPresent(renderer);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
