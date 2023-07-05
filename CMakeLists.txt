cmake_minimum_required(VERSION 3.24)
project(merlin)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic")

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(merlin src/main.cpp)