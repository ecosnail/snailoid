#include "view.hpp"
#include "exceptions.hpp"

View::View(const Configuration::View& config)
    : _window(nullptr)
    , _renderer(nullptr)
    , _gameState(nullptr)
{
    _window = SDL_CreateWindow(
        config.title.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        config.screen_width,
        config.screen_height,
        SDL_WINDOW_SHOWN);
    if (!_window) {
        THROW(SdlException);
    }

    _renderer = SDL_CreateRenderer(
        _window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer) {
        THROW(SdlException);
    }
}

View::~View()
{
    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
    }
    if (_window) {
        SDL_DestroyWindow(_window);
    }
}

void View::attach(const GameState &gameState)
{
    _gameState = &gameState;
}

void View::render()
{
    if (!_gameState) {
        return;
    }

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    int ballScreenX = _gameState->_ball.geometry.center().x() * 800;
    int ballScreenY = _gameState->_ball.geometry.center().y() * 600;
    circleRGBA(_renderer, ballScreenX, ballScreenY, 10, 0, 255, 255, 255);

    SDL_RenderPresent(_renderer);
}