#ifndef GUARD_Activity
#define GUARD_Activity

#include <chrono>
#include <string>
#include <SQLiteCpp/SQLiteCpp.h>

struct Period {
    using Clock = std::chrono::system_clock;

    Period(typename Clock::time_point start_, typename Clock::time_point end_);

    typename Clock::time_point start;
    typename Clock::time_point end;

    typename Clock::duration duration() const {
        return (end - start);
    }
};

class Activity {
public:
    Activity(std::string name, std::string description, Period period);

    const std::string& getName() const {
        return name;
    }
    void setName(const std::string& name) {
        this->name = name;
    }

    const std::string& getDescription() const {
        return name;
    }
    void setDescription(const std::string& name) {
        this->name = name;
    }

    const Period& getPeriod() const {
        return period;
    }
    void setPeriod(const Period& period) {
        this->period = period;
    }

    int loadToDb(SQLite::Database& db);

private:  
    std::string name;
    std::string description;
    Period period;
};

#endif
