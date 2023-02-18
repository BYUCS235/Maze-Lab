cmake_minimum_required(VERSION 3.24)
project(maze_lab)

set(CMAKE_CXX_STANDARD 17)

add_executable(maze maze.cpp)

add_executable(validate validate.cpp)
