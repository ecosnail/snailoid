#pragma once

#include "configuration.hpp"
#include "game_state.hpp"
#include "sdl_libs.hpp"

class View {
public:
    View(const Configuration::View& config);
    ~View();

    void attach(const GameState &gameState);
    void render();

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    const GameState* _gameState;
};