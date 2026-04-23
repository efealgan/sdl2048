cmake_minimum_required(VERSION 3.24)
project(initialSDL)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#sdl things
add_subdirectory(vendored)

add_executable(${PROJECT_NAME})

#game
add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} PRIVATE vendored)