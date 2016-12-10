#pragma once

#include <SDL2/SDL.h>

#include <exception>
#include <string>
#include <sstream>

#define THROW(EXCEPTION) throw EXCEPTION(__FILE__, __LINE__)
#define THROWA(EXCEPTION, ...) throw EXCEPTION(__FILE__, __LINE__, __VA_ARGS__)

class Exception : public std::exception {
public:
    Exception(const char *file, size_t line, std::string message)
        : _file(std::move(file))
        , _line(line)
        , _userMessage(message)
    { }

    virtual const char * what() const noexcept override
    {
        return (_file + ":" + std::to_string(_line) + ": " + _userMessage).c_str();
    }

protected:
    std::string _file;
    size_t _line;
    std::string _userMessage;
};

class SdlException : public Exception {
public:
    SdlException(const char *file, size_t line, std::string message = "")
        : Exception(file, line, message)
    {
        _sdlMessage = SDL_GetError();
    }

    virtual const char * what() const noexcept override
    {
        return (_file + ":" + std::to_string(_line) + ": SDL error '" + _sdlMessage + "'" +
            (_userMessage == "" ? "" : ": " + _userMessage)).c_str();
    }

private:
    std::string _sdlMessage;
};
