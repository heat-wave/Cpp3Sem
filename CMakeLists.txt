cmake_minimum_required(VERSION 2.8.4)

project(big_integer)

include_directories(${SOURCE_DIR})
include_directories(${SOURCE_DIR}/big_integer)
include_directories(${SOURCE_DIR}/big_integer/gtest})
add_definitions(--std=c++11)

set(SOURCE_FILES big_integer/main.cpp big_integer/big_integer.cpp)

add_executable(	big_integer

					big_integer/big_integer.hpp
					big_integer/big_integer.cpp
					big_integer/exception.cpp
					big_integer/main.cpp)

add_executable(	big_integer_test

					big_integer/big_integer_test.cpp
					big_integer/big_integer.hpp
					big_integer/big_integer.cpp
					big_integer/exception.cpp
					big_integer/gtest/gtest-all.cc
					big_integer/gtest/gtest.hpp
					big_integer/gtest/gtest_main.cc)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -w -std=gnu++0x")
endif()

target_link_libraries(big_integer_test -lgmp -lgmpxx -lpthread)