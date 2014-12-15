cmake_minimum_required(VERSION 2.8.4)
project(big_integer)

add_definitions(--std=c++11)

set(SOURCE_FILES big_integer/big_integer.hpp big_integer/main.cpp big_integer/big_integer.cpp)
add_executable(big_integer ${SOURCE_FILES})