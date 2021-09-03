cmake_minimum_required(VERSION 3.17)
set(target integral_image)

project(${target})
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(${target} source/main.cpp)
target_link_libraries(${target} ${OpenCV_LIBS})

