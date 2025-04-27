cmake_minimum_required(VERSION 3.31)

project(guess_it C)

find_package(SQLite3 REQUIRED)
if(SQLite3_FOUND)
    include_directories(${SQLite3_INCLUDE_DIRS})
    add_executable(guess_it src/main.c)
    target_link_libraries(guess_it SQLite::SQLite3)
else()
    message(WARNING "SQLite3 not found, using amalgamated source.")
    add_executable(guess_it src/main.c sqlite/sqlite3.c)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sqlite)
endif()


