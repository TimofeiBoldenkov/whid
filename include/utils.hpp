#ifndef GUARD_utils
#define GUARD_utils

#include <chrono>
#include <ctime>

namespace utils
{
    std::chrono::system_clock::time_point makeTimePoint(int year, int month, int day, int hour, int min, int sec);
};

#endif
