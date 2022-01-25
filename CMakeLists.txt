cmake_minimum_required(VERSION 3.14)

# set the project name
project(ParallelQuantLib VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(external/googletest)
add_subdirectory(src)
add_subdirectory(src/test)

include_directories(external/googletest/include)
include_directories(src)
include_directories(src/test)

configure_file(src/main.h.in src/main.h)

# add the executables
add_executable(ParallelQuantLib src/main.cpp)
# add_executable(Binomial src/binomial.cpp)
add_executable(Test src/test/test.cpp)

# link libraries
target_link_libraries(ParallelQuantLib PUBLIC Source)
target_link_libraries(Test PRIVATE gtest_main) # link gtest to this executable

# add the binary tree to the search path for include files
target_include_directories(ParallelQuantLib PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src"
                           )