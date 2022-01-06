cmake_minimum_required(VERSION 3.10)

# set the project name
project(ParallelQuantLib VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(main.h.in main.h)

add_library(Binomial binomial.cpp)

# add the executable
add_executable(ParallelQuantLib main.cpp)

target_link_libraries(ParallelQuantLib PUBLIC Binomial)

# add the binary tree to the search path for include files
target_include_directories(ParallelQuantLib PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )