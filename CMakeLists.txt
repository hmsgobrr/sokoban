cmake_minimum_required(VERSION 3.0)
project(sokoban CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_source_files_properties(glad/src/glad.c PROPERTIES LANGUAGE C)
add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PRIVATE glad/include)

file(GLOB SOURCE "src/*.cpp" "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCE})

if (CMAKE_GENERATOR MATCHES "Visual Studio 17 2022")
	target_include_directories(${PROJECT_NAME} PUBLIC "D:/include")
	target_link_directories(${PROJECT_NAME} PUBLIC "D:/lib-vs2022")
endif()

target_link_libraries(${PROJECT_NAME} glfw3)
if(UNIX)
target_link_libraries(GL pthread dl m)
endif()

target_link_libraries(${PROJECT_NAME} glad)

target_include_directories(${PROJECT_NAME} PRIVATE include glad/include)
target_compile_definitions(${PROJECT_NAME} PUBLIC SHADERS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/shaders" ASSETS="${CMAKE_CURRENT_SOURCE_DIR}/assets")
