#include <utils.hpp>

std::chrono::system_clock::time_point utils::makeTimePoint(int year, int month, int day, int hour, int min, int sec) {
    std::tm time;
    time.tm_year = year;
    time.tm_mon = month;
    time.tm_mday = day;
    time.tm_hour = hour;
    time.tm_min = min;
    time.tm_sec = sec;

    return std::chrono::system_clock::from_time_t(std::mktime(&time));
}