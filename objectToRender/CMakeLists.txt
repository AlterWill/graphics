cmake_minimum_required(VERSION 3.20)

project(tiny_renderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)

add_executable(tiny_renderer
    src/main.cpp
)

target_include_directories(tiny_renderer PRIVATE
    include
)

target_link_libraries(tiny_renderer PRIVATE
    SDL3::SDL3
)
