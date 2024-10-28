cmake_minimum_required(VERSION 3.30)
project(crumbyColouring)

set(CMAKE_CXX_STANDARD 11)

add_executable(naiveCrumbyColouring checkCrumbyColouring.cpp
        naiveCrumbyColouring.cpp
        checkCrumbyColouring.h
        graphLoader.h
        graphLoader.cpp)

add_executable(smartCrumbyColouring checkCrumbyColouring.cpp
        checkCrumbyColouring.h
        graphLoader.h
        smartCrumbyColouring.cpp
        graphLoader.cpp)