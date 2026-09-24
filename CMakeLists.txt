cmake_minimum_required(VERSION 3.20)

project(OpenGLProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)

add_executable(OpenGLProject
    src/gravity.cpp
)

target_link_libraries(OpenGLProject PRIVATE glfw "-framework OpenGL")