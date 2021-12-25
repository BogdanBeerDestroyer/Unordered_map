cmake_minimum_required(VERSION 3.21)
project(unordered_map_project)

#set(CMAKE_CXX_FLAGS "&{CMAKE_CXX_FLAGS} -std=c++200")
add_subdirectory(for_gtests/googletest)

include_directories(for_gtests/googletest/googletest/include)
add_executable(GoogleTestDemo tests.cpp)
add_executable(demo main.cpp)
target_link_libraries(GoogleTestDemo gtest gtest_main)