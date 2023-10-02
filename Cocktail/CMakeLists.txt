cmake_minimum_required(VERSION 3.16)
project(Cocktail)

set(CMAKE_CXX_STANDARD 20)

add_library(Cocktail STATIC source/Cocktail.cpp)

target_include_directories(Cocktail PUBLIC include)

target_link_libraries(Cocktail LibUtils)