cmake_minimum_required(VERSION 3.22.1)

project(KDEAirPods VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

find_package(sdbus-c++ REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(KDEAirPods ${SOURCES})
target_include_directories(KDEAirPods PRIVATE src)
target_link_libraries(KDEAirPods PRIVATE sdbus-c++ bluetooth)
