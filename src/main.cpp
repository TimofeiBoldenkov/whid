#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <vector>
#include <iterator>
#include <utils.hpp>
#include <Activity.hpp>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Invalid arguments" << std::endl;
        return 1;
    }


    char *databaseName = argv[1];
    if (std::filesystem::exists(std::filesystem::path(databaseName))) 
        std::cout << "Opening " << databaseName << "..." << std::endl;
    else
        std::cout << "Creating " << databaseName << "..." << std::endl;
    
    SQLite::Database db(databaseName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    SQLite::Statement(db, "CREATE TABLE IF NOT EXISTS activities (\n"
                                             "id          INTEGER PRIMARY KEY,\n"
                                             "name        TEXT    NOT NULL,\n"
                                             "description TEXT,\n"
                                             "start       INTEGER NOT NULL,\n"
                                             "end         INTEGER NOT NULL);").exec();

    std::string action;
    do {
        try {
            std::cout << "What do you want to do?" << std::endl;
            std::cout << "1. Get all the activities you've ever made" << std::endl;
            std::cout << "2. Get all the activities for a certain period" << std::endl;
            std::cout << "3. Get statistics for a certain period" << std::endl;
            std::cout << "4. Add a new activity" << std::endl;
            std::cout << "5. Save and exit" << std::endl;
            std::cout << "6. Exit without saving" << std::endl;

            std::cout << "> ";
            std::getline(std::cin, action);


            if (action == "4") {
                std::cout << "Write name of the activity\n> ";
                std::string name;
                std::getline(std::cin, name);
                std::cout << "Write description of the activity\n> ";
                std::string description;
                std::getline(std::cin, description);

                std::cout << "Write start date of the activity (YYYY MM DD)\n> ";
                std::tm startTime{};
                std::string dateString;
                std::getline(std::cin, dateString);
                std::vector<std::string> date;
                utils::split(dateString, std::back_inserter(date));
                if (date.size() != 3)
                    throw std::invalid_argument("");
                startTime.tm_year = std::stoi(date[0]) - 1900;
                startTime.tm_mon = std::stoi(date[1]) - 1;
                startTime.tm_mday = std::stoi(date[2]);
                if (startTime.tm_mon < 1 || startTime.tm_mon > 12 || startTime.tm_mday < 1 || startTime.tm_mday > 31)
                    throw std::invalid_argument("");
                std::cout << "Write start time of the activity (HH MM)\n> ";
                std::string timeString;
                getline(std::cin, timeString);
                std::vector<std::string> time;
                utils::split(timeString, std::back_inserter(time));
                if (time.size() != 2)
                    throw std::invalid_argument("");
                startTime.tm_hour = std::stoi(time[0]);
                startTime.tm_min = std::stoi(time[1]);
                if (startTime.tm_hour < 0 || startTime.tm_hour > 23 || startTime.tm_min < 0 || startTime.tm_min > 59)
                    throw std::invalid_argument("");

                std::cout << "Write end date of the activity (YYYY MM DD)\n> ";
                std::tm endTime{};
                std::getline(std::cin, dateString);
                date = std::vector<std::string>();
                utils::split(dateString, std::back_inserter(date));
                if (date.size() != 3)
                    throw std::invalid_argument("");
                endTime.tm_year = std::stoi(date[0]) - 1900;
                endTime.tm_mon = std::stoi(date[1]) - 1;
                endTime.tm_mday = std::stoi(date[2]);
                if (endTime.tm_mon < 1 || endTime.tm_mon > 12 || endTime.tm_mday < 1 || endTime.tm_mday > 31)
                    throw std::invalid_argument("");
                std::cout << "Write end time of the activity (HH MM)\n> ";
                getline(std::cin, timeString);
                time = std::vector<std::string>();
                utils::split(timeString, std::back_inserter(time));
                if (time.size() != 2)
                    throw std::invalid_argument("");
                endTime.tm_hour = std::stoi(time[0]);
                endTime.tm_min = std::stoi(time[1]);
                if (endTime.tm_hour < 0 || endTime.tm_hour > 23 || endTime.tm_min < 0 || endTime.tm_min > 59)
                    throw std::invalid_argument("");

                Activity activity(name, description, 
                         Period(utils::makeTimePoint(startTime), utils::makeTimePoint(endTime)));
                activity.loadToDb(db);
            }
        } catch (std::invalid_argument) {
            std::cout << "Invalid input" << std::endl;
            continue;
        }

    } while (action != "5" && action != "6");

    return 0;
}
