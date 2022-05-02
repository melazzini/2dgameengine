cmake_minimum_required(VERSION 3.7..3.21 FATAL_ERROR)

project(2dgameengine LANGUAGES CXX)

add_subdirectory(src)

add_executable(app main.cpp)

target_link_libraries(app mysimple2dgameengine)

