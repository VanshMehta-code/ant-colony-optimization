cmake_minimum_required(VERSION 3.23)
project(aco-project)
add_executable(aco-project)
target_sources(aco-project 
  PRIVATE 
    src/main.cpp 
    src/math.c
  PUBLIC
  FILE_SET headers
  TYPE HEADERS
  BASE_DIRS include
  FILES 
  include/aco_math.h
)
target_link_libraries(aco-project PRIVATE raylib GL m pthread dl rt X11)
