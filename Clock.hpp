#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <chrono>

class Clock
{
private:
    std::chrono::high_resolution_clock::time_point startTime, endTime;
    std::chrono::duration<double> timespan;

public:
    void start();
    void end();
    double elapsedTime();
};

#endif