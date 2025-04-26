#include <iostream>
#include <exception>
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/Statement.h>

int main()
{
    try {
        SQLite::Database db("example.db");

        SQLite::Statement query(db, "SELECT * FROM test WHERE size > ?");

        query.bind(1, 6);

        while (query.executeStep()) {
            int         id      = query.getColumn(0);
            const char *value   = query.getColumn(1);
            int         size    = query.getColumn(2);

            std::cout << "row: " << id << ", " << value << ", " << size << std::endl;
        }

    } catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }

    return 0;
}
