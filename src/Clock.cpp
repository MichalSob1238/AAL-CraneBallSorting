#include "Clock.hpp"

void Clock::start()
{
    startTime = std::chrono::high_resolution_clock::now();
}

void Clock::end()
{
    endTime = std::chrono::high_resolution_clock::now();
    timespan = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
}

double Clock::elapsedTime()
{
    return timespan.count();
}