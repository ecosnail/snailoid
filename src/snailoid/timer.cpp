#include "timer.hpp"

Timer::Timer()
    : _start(Clock::now())
{ }

double Timer::get() const
{
    auto current = Clock::now();
    return std::chrono::duration<double>(current - _start).count();
}

double Timer::reset()
{
    auto current = Clock::now();
    double delta = std::chrono::duration<double>(current - _start).count();
    _start = current;
    return delta;
}