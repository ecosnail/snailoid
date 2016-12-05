#pragma once

#include <chrono>

class FrameTimer {
public:
	FrameTimer(float fps)
		: _timePerFrame(1.0f / fps)
		, _prevTime(Clock::now())
	{ }

	bool itIsTime()
	{
		auto currentTime = Clock::now();
		if (currentTime - _prevTime >= _timePerFrame) {
			_prevTime = currentTime;
			return true;
		}
		return false;
	}

private:
	typedef std::chrono::high_resolution_clock Clock;

	std::chrono::duration<float> _timePerFrame;
	std::chrono::time_point<Clock> _prevTime;
};
