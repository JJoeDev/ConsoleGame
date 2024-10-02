cmake_minimum_required(VERSION 3.28)
project(Console)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC})
