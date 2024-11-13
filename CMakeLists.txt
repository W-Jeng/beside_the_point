cmake_minimum_required(VERSION 3.10)

project(beside_the_point)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(main src/main.cpp)