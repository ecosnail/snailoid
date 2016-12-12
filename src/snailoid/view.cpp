#include "view.hpp"
#include "exceptions.hpp"

#include <cmath>
#include <utility>

Viewport::Viewport()
    : _gameLeftX(0), _gameBottomY(1.0f)
    , _screenLeftX(0), _screenBottomY(10)
    , _widthRatio(1.0f), _heightRatio(1.0f)
{ }

Viewport::Viewport(
        game::Coord gameLeftX, game::Coord gameBottomY,
        screen::Coord screenLeftX, screen::Coord screenBottomY,
        float widthRatio, float heightRatio)
    : _gameLeftX(std::move(gameLeftX))
    , _gameBottomY(std::move(gameBottomY))
    , _screenLeftX(std::move(screenLeftX))
    , _screenBottomY(std::move(screenBottomY))
    , _widthRatio(widthRatio)
    , _heightRatio(heightRatio)
{ }

Viewport Viewport::simple2d(
    const game::AxisRect& srcRect,
    const screen::Rect& dstRect)
{
    return Viewport(
        srcRect.xStart(), srcRect.yStart(),
        dstRect.xStart(), dstRect.yEnd(),
        dstRect.w() / srcRect.w(), dstRect.h() / srcRect.h());
}

screen::Coord Viewport::floor(const game::Coord& gameCoord) const
{
    return static_cast<screen::Coord>(std::floor(gameCoord));
}

screen::Coord Viewport::ceil(const game::Coord& gameCoord) const
{
    return static_cast<screen::Coord>(std::ceil(gameCoord));
}

screen::Point Viewport::transformPoint(const game::Point& gamePoint) const
{
    return screen::Point(
        _screenLeftX + floor((gamePoint.x() - _gameLeftX) * _widthRatio),
        _screenBottomY - floor((gamePoint.y() - _gameBottomY) * _heightRatio));
}

screen::Ellipse Viewport::transformCircle(const game::Circle& gameCircle) const
{
    return screen::Ellipse(
        transformPoint(gameCircle.center()),
        ceil(gameCircle.radius() * _widthRatio),
        ceil(gameCircle.radius() * _heightRatio));
}

screen::Rect Viewport::transformRect(const game::AxisRect& gameRect) const
{
    return screen::Rect(
        transformPoint(gameRect.start()),
        transformPoint(gameRect.end()));
}


View::View(const Configuration::View& config)
    : _window(nullptr)
    , _renderer(nullptr)
    , _gameState(nullptr)
    , _width(0)
    , _height(0)
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

    SDL_GetWindowSize(_window, &_width, &_height);

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
        _width = 0;
        _height = 0;
    }
}

void View::setViewport(Viewport viewport)
{
    _viewport = std::move(viewport);
}

void View::attach(const game::State &gameState)
{
    _gameState = &gameState;
}

void View::renderBall(const game::Ball& ball)
{
    static const SDL_Color BallColor = { 0, 255, 255, 255 };

    screen::Ellipse ellipse =
        _viewport.transformCircle(ball.geometry);

    filledEllipseRGBA(
        _renderer,
        ellipse.x(), ellipse.y(),
        ellipse.rx(), ellipse.ry(),
        BallColor.r, BallColor.g, BallColor.b, BallColor.a);


}

void View::renderBlock(const game::Block& block)
{
    static const Uint32 BlockColor = 0xFFFF00FF;

    screen::Rect rect = _viewport.transformRect(block.geometry);

    rectangleColor(
        _renderer,
        rect.xStart(), rect.yStart(),
        rect.xEnd(), rect.yEnd(),
        BlockColor);
}

void View::render()
{
    if (!_gameState) {
        return;
    }

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    renderBall(_gameState->ball);
    //for (const game::Block& block : _gameState->blocks) {
    //    renderBlock(block);
    //}

    //circleRGBA(_renderer, 500, 500, 20, 255, 0, 0, 255);
    //filledEllipseRGBA(_renderer, 500, 500, 20, 30, 255, 0, 0, 255);

    

    //filledEllipseRGBA(_renderer, 513, 690, 52, 39, 0, 255, 255, 255);

    SDL_RenderPresent(_renderer);
}
