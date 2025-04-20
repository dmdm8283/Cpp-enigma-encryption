cmake_minimum_required(VERSION 3.10)
project(enigma101)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(enigma101 main.cpp
        keys.cpp
        keys.h
        rotors.cpp
        rotors.h)
target_link_libraries(enigma101 ${SDL2_LIBRARIES})
