#include <Activity.hpp>
#include <bits/chrono.h>
#include <utils.hpp>
#include <cstdint>

Period::Period(typename Clock::time_point start_, typename Clock::time_point end_) : start(start_), end(end_) { }

Activity::Activity(std::string name_, std::string description_, Period period_) : name(name_), description(description_), period(period_) { }

int Activity::loadToDb(SQLite::Database& db)
{
    SQLite::Statement insertStatement(db, "INSERT INTO activities (NAME,DESCRIPTION,START,END) VALUES (?, ?, ?, ?)");
    insertStatement.bind(1, name);
    insertStatement.bind(2, description);
    std::int64_t start = std::chrono::duration_cast<std::chrono::seconds>(period.start.time_since_epoch()).count();
    insertStatement.bind(3, start);
    std::int64_t end = std::chrono::duration_cast<std::chrono::seconds>(period.end.time_since_epoch()).count();
    insertStatement.bind(4, end);
    
    return insertStatement.exec();
}
