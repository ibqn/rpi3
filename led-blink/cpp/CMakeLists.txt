cmake_minimum_required(VERSION 3.0)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CheckIncludeFile)
check_include_file("wiringPi.h" HAVE_WIRING_PI_H)
if(NOT HAVE_WIRING_PI_H)
    message( FATAL_ERROR "wiringPi library not found!" )
endif()

project(LED-Blink)

add_executable(led-blink main.cpp)

target_link_libraries(led-blink -lwiringPi)