#include "media.hpp"
#include "exceptions.hpp"
#include "sdl_libs.hpp"

#include <utility>

Media* Media::_media = nullptr;

void Media::initialize(Configuration::View viewConfiguration)
{
    if (_media) {
        THROWA(Exception, "Media initialized twice");
    }
    _media = new Media(viewConfiguration);
}

Media& Media::instance()
{
    if (!_media) {
        THROWA(Exception, "Media is not initialized before use");
    }
    return *_media;
}

Media::Media(Configuration::View viewConfiguration)
    : _viewConfiguration(std::move(viewConfiguration))
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        THROW(SdlException);
    }
}

Media::~Media()
{
    SDL_Quit();
}

View Media::makeView()
{
    return View(_viewConfiguration);
}




Media& media()
{
    return Media::instance();
}