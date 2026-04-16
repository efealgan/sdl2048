cmake_minimum_required(VERSION 3.24)
project(initialSDL)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#sdl things
add_subdirectory(vendored)

#game
add_subdirectory(src)