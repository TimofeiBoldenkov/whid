#ifndef GUARD_Activity
#define GUARD_Activity

#include <chrono>
#include <string>

template <typename Clock = std::chrono::system_clock>
struct Period {

    Period(Clock::time_point start, Clock::time_point end);

    Clock::time_point start;
    Clock::time_point end;

    Clock::duration duration() const {
        return (end - start);
    }
};

class Activity {
public:
    Activity(std::string name, std::string description, Period<std::chrono::system_clock> period);

private:  
    std::string name;
    std::string description;
    Period<std::chrono::system_clock> period;
};

#endif
