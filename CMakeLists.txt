cmake_minimum_required(VERSION 3.17)

project(integral_image)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED)
find_package(OpenMP REQUIRED)
find_package(GTest REQUIRED)

add_library(lib STATIC source/Image.cpp source/Image.h source/ImageChannel.cpp source/ImageChannel.h)
target_include_directories(lib PRIVATE ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
target_link_libraries(lib ${OpenCV_LIBS} Boost::program_options OpenMP::OpenMP_CXX)

add_executable(integral_image source/main.cpp)
target_include_directories(integral_image PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(integral_image lib)

add_executable(test test/main.cpp)
target_link_libraries(test PRIVATE lib GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
