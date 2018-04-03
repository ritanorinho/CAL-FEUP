cmake_minimum_required(VERSION 3.9)
project(CAL-FEUP)

set(CMAKE_CXX_STANDARD 11)
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
add_executable(untitled $(SOURCE_FILES))