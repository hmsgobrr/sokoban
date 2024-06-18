cmake_minimum_required(VERSION 3.0)
project(sokoban CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_source_files_properties(glad/src/glad.c PROPERTIES LANGUAGE C)
add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PRIVATE glad/include)

add_subdirectory(soko)
add_subdirectory(line)

