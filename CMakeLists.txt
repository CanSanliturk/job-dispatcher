cmake_minimum_required(VERSION 3.10)

project(job-dispatcher)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options for build type
option(BUILD_DEBUG "Build in debug mode" ON)

# Set build type
if(BUILD_DEBUG)
    set(CMAKE_BUILD_TYPE "Debug")
elseif(BUILD_DEBUG)
    set(CMAKE_BUILD_TYPE "Release")
endif()

# Find all .cpp files under include and src directory
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add executable
add_executable(job-dispatcher main.cpp ${SOURCES})
