#include <utils.hpp>
#include <sstream>

std::chrono::system_clock::time_point utils::makeTimePoint(int year, int month, int day, int hour, int min, int sec) {
    std::tm time;
    time.tm_year = year - 1900;
    time.tm_mon = month - 1;
    time.tm_mday = day;
    time.tm_hour = hour;
    time.tm_min = min;
    time.tm_sec = sec;

    return std::chrono::system_clock::from_time_t(std::mktime(&time));
}

std::chrono::system_clock::time_point utils::makeTimePoint(std::tm time) {
    return std::chrono::system_clock::from_time_t(std::mktime(&time));
}

int utils::getNextId(const SQLite::Database& db, const std::string& table)
{
    SQLite::Statement query(db, "SELECT max(id) FROM " + table);
    int nextId;
    if (!query.executeStep())
        nextId = 1;
    else {
        nextId = static_cast<int>(query.getColumn(0)) + 1;
    }

    return nextId;
}