cmake_minimum_required(VERSION 3.21)
project(unordered_map_project)

add_subdirectory(for_gtests/googletest)

include_directories(for_gtests/googletest/googletest/include)
add_executable(GoogleTestDemo tests.cpp)
add_executable(demo main.cpp)
target_link_libraries(GoogleTestDemo gtest gtest_main)