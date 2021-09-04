cmake_minimum_required(VERSION 3.17)
set(target integral_image)

project(${target})

find_package(OpenCV REQUIRED)
find_package(MPI REQUIRED)
find_package(Boost COMPONENTS program_options mpi REQUIRED)
find_package(OpenMP REQUIRED)

add_executable(${target} source/main.cpp)
target_include_directories(${target} PRIVATE ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
target_link_libraries(${target} ${OpenCV_LIBS} ${MPI_LIBRARIES} Boost::program_options Boost::mpi OpenMP::OpenMP_CXX)
set_target_properties(${target} PROPERTIES CXX_STANDARD 17)
