add_subdirectory(SDL_ttf)
add_subdirectory(SDL)

add_library(vendored INTERFACE)
target_link_libraries(vendored INTERFACE SDL3_ttf::SDL3_ttf SDL3::SDL3)