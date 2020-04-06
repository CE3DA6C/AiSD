#pragma once
#include <chrono>
#include <iostream>
#include <thread>

class Timer
{
    std::chrono::duration<float> duration;
    std::chrono::time_point<std::chrono::steady_clock> start, end;
public:


    Timer()
    {
        start = std::chrono::steady_clock::now();
    }

    float elapsedTime()
    {
        end = std::chrono::steady_clock::now();
        duration = end - start;
        float ms = duration.count() * 1000.0f;
       
        return ms;
    }
    void reset() {
        start = std::chrono::steady_clock::now();
        duration = duration.zero();
    }
};