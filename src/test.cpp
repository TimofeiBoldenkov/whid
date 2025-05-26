#include <string>
#include <iterator>
#include <vector>
#include <iostream>
#include <exception>
#include <sstream>
#include <algorithm>
#include <SQLiteCpp/SQLiteCpp.h>

template<typename Out>
Out split(const std::string& str, Out dest)
{
    std::istringstream sin(str);
    
    std::string word;
    while (sin >> word) {
        *dest++ = word;
    }

    return dest;
}

template<typename In>
std::ostream& print(std::ostream& os, In b, In e, std::string sep = " ", std::string begin = "", std::string end = "\n")
{
    os << begin;

    if (b != e) {
        os << *b++;
    }

    for (; b != e; b++) {
        os << sep << *b;
    }

    os << end;

    return os;
}

int countColumns(const SQLite::Database& db, const std::string& table)
{
    SQLite::Statement query(db, "PRAGMA table_info(" + table + ");");

    int count = 0;
    while (query.executeStep())
        count++;
    
    return count;
}

std::vector<std::string> getColumnNames(const SQLite::Database& db, const std::string& table)
{
    std::vector<std::string> names;

    SQLite::Statement query(db, "SELECT name FROM pragma_table_info('" + table + "')");

    while (query.executeStep()) {
        names.push_back(query.getColumn(0));
    }

    return names;
}

int getNextId(const SQLite::Database& db, const std::string& table)
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

int main()
{
    try {
        SQLite::Database db("../example.db", SQLite::OPEN_READWRITE);

        std::string line;
        while (std::getline(std::cin, line)) {
            std::vector<std::string> values;
            split(line, std::back_inserter(values));

            int insertValuesNumber = std::min(countColumns(db, "test"), static_cast<int>(values.size()) + 1);

            std::string insertQueryText = "INSERT INTO test(ID";
            std::vector<std::string> columnNames = getColumnNames(db, "test");
            for (int i = 1; i < insertValuesNumber; i++) {
                insertQueryText += ", " + columnNames[i];
            }
            insertQueryText += ") VALUES(" + std::to_string(getNextId(db, "test"));
            for (int i = 0; i < insertValuesNumber - 1 && i < values.size(); i++) {
                insertQueryText += ", " + values[i];
            }
            insertQueryText += ")";

            db.exec(insertQueryText);
        }

    } catch (SQLite::Exception& e) {
        std::clog << "exception: " << e.what() << std::endl;
    }

    return 0;
}
