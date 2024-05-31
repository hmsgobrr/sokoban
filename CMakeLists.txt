cmake_minimum_required(VERSION 3.0)
project(sokoban CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE "src/*.cpp" "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} glfw GL pthread dl m)

add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PRIVATE glad/include)
target_link_libraries(${PROJECT_NAME} glad)

target_include_directories(${PROJECT_NAME} PRIVATE include glad/include)
target_compile_definitions(${PROJECT_NAME} PUBLIC SHADERS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/shaders" ASSETS="${CMAKE_CURRENT_SOURCE_DIR}/assets")

