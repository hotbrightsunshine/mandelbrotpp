cmake_minimum_required(VERSION 3.10)
project(mandelbrotpp)

set(CMAKE_CXX_STANDARD 23)

message("SDL2 include dirs: ${SDL_LIBRARIES}")

add_subdirectory(libs)

add_executable(mandelbrotpp "src/main.cxx")
target_link_libraries(mandelbrotpp mandelbrot SDL2)