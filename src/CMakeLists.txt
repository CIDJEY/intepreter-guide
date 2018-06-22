cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

add_definitions(-std=gnu++14)
add_definitions(-O0 -D_DEBUG -g)

file(GLOB_RECURSE SRCS *.cpp)

add_executable(intepreter ${SRCS})