cmake_minimum_required(VERSION 3.10)

project(beside_the_point)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(monte_carlo src/monte_carlo.cpp)
add_executable(adaptive_boole src/adaptive_boole.cpp)
add_executable(adaptive_simpson src/adaptive_simpson.cpp)
add_executable(quad_triple src/quad_triple.cpp)
add_executable(simpson_triple src/simpson_triple.cpp)