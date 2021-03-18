# Project Settings
cmake_minimum_required(VERSION 3.1)
project(gltest)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)

# The main executable
add_executable(gltest src/gltest.cpp src/loadShader.cpp)
set_property(TARGET gltest PROPERTY CXX_STANDARD 17)
target_compile_options(gltest PRIVATE -Wall)
target_link_libraries(gltest PRIVATE GL glfw GLEW)
include_directories("include")
