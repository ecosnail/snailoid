#pragma once

#include "configuration.hpp"
#include "game_state.hpp"
#include "sdl_libs.hpp"
#include "screen_space.hpp"

/**
 * Mapping between 2 areas, in game space and in screen space.
 */
class Viewport {
public:
    Viewport();

    static Viewport simple2d(
        const game::AxisRect& srcRect,
        const screen::Rect& dstRect);

    screen::Point transformPoint(const game::Point& gamePoint) const;
    screen::Ellipse transformCircle(const game::Circle& gameCircle) const;
    screen::Rect transformRect(const game::AxisRect& gameRect) const;
    
private:
    Viewport(
        game::Coord gameLeftX, game::Coord gameBottomY,
        screen::Coord screenLeftX, screen::Coord screenBottomY,
        float widthRatio, float heightRatio);

    screen::Coord floor(const game::Coord& gameCoord) const;
    screen::Coord ceil(const game::Coord& gameCoord) const;

    game::Coord _gameLeftX;
    game::Coord _gameBottomY;
    screen::Coord _screenLeftX;
    screen::Coord _screenBottomY;
    float _widthRatio;
    float _heightRatio;
};

class View {
public:
    View(const Configuration::View& config);
    ~View();

    void setViewport(Viewport viewport);

    void attach(const game::State &gameState);
    void render();

private:
    void renderBall(const game::Ball& ball);
    void renderBlock(const game::Block& block);

    SDL_Window* _window;
    SDL_Renderer* _renderer;
    const game::State* _gameState;
    Viewport _viewport;

    screen::Coord _width;
    screen::Coord _height;
};