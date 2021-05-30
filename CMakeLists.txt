cmake_minimum_required(VERSION 3.19)

project(metrics_lab LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if(CMAKE_COMPILER_IS_GNUCC)
    message(STATUS "Detected GNU compiler. Using specific flags.")
    set(CMAKE_CXX_FLAGS_DEBUG "-pipe -Wall -Wextra -Wpedantic -O0 -ggdb --coverage")
    set(CMAKE_CXX_FLAGS_RELEASE "-pipe -march=native -O3")
    set(CMAKE_CXX_FLAGS "-Wno-unused-parameter")
endif()

add_subdirectory(lun)
add_subdirectory(me)
#add_subdirectory(mike)
