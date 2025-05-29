#ifndef GUARD_utils
#define GUARD_utils

#include <chrono>
#include <ctime>
#include <string>
#include <SQLiteCpp/SQLiteCpp.h>

namespace utils
{
    std::chrono::system_clock::time_point makeTimePoint(int year, int month, int day, int hour = 0, int min = 0, int sec = 0);
    
    std::chrono::system_clock::time_point makeTimePoint(std::tm time);
    
    template <typename Out>
    Out split(const std::string& str, Out dest)
    {
        std::istringstream sin(str);
        
        std::string word;
        while (sin >> word) {
            *dest++ = word;
        }

        return dest;
    }

    int getNextId(const SQLite::Database& db, const std::string& table);
};

#endif
