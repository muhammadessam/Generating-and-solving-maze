cmake_minimum_required(VERSION 3.8)
project(MazeSolution)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c includ/main.h includ/arraysindex.h src/arraysindex.c)
link_libraries(cs m)
add_executable(MazeSolution ${SOURCE_FILES})