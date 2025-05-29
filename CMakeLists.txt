set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
project(whid LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/thirdparty/SQLiteCpp)

add_library(whid_lib 
    src/utils.cpp
    src/Activity.cpp
)
target_link_libraries(whid_lib PUBLIC
    SQLiteCpp
    sqlite3
)
set(PROJECT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
target_include_directories(whid_lib PUBLIC 
    ${PROJECT_INCLUDE_DIR}
)

add_executable(whid src/main.cpp)
target_link_libraries(whid PRIVATE whid_lib)

