cmake_minimum_required(VERSION 3.26)
project(final)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Release)

# source files
file(GLOB EJ_UNO ejercicioDiez.cpp)


# binaries
add_executable(ejercicioDiez ${EJ_UNO})

