add_subdirectory(SDL)
add_subdirectory(SDL_ttf)

add_library(vendored INTERFACE)

target_include_directories(vendored INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/SDL/include
    ${CMAKE_CURRENT_SOURCE_DIR}/SDL_ttf/include
)

target_link_libraries(vendored INTERFACE 
    SDL3::SDL3 
    SDL3_ttf::SDL3_ttf
)