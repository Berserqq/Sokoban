cmake_minimum_required(VERSION 3.16)

project(Sokoban C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
)

set(SOURCES
    src/main.c
    src/game.c
    src/input.c
    src/level.c
    src/menu.c
    src/render.c
    src/save.c
    src/history.c
)

add_executable(sokoban ${SOURCES})

enable_testing()

add_executable(sokoban_tests
    tests/test_game.c
)

add_test(NAME SokobanTests COMMAND sokoban_tests)

file(COPY levels DESTINATION ${CMAKE_BINARY_DIR})