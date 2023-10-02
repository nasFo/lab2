cmake_minimum_required(VERSION 3.16)
project(Bar)

set(CMAKE_CXX_STANDARD 20)

add_library(Bar STATIC source/Bar.cpp)

target_include_directories(Bar PUBLIC include)

target_link_libraries(Bar Cocktail LibUtils)