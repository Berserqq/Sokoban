cmake_minimum_required(VERSION 3.10)

project(Sokoban C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(sokoban
    src/main.c
    src/game.c
    src/input.c
    src/level.c
    src/menu.c
    src/render.c
)