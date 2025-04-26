cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(whid LANGUAGES CXX)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/thirdparty/SQLiteCpp)

add_executable(whid src/main.cpp)

target_link_libraries(whid
    SQLiteCpp
    sqlite3
)
