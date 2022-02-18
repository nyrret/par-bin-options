# Getting the Code

After cloning, initialize external repositories by running 

    git submodule update --init
    
Make parlaylib by following the "Installing and including via CMake" instructions here: https://github.com/cmuparlay/parlaylib/tree/493fba05b10753fa17325c9cb72dc7100db9c7bb

Make google test by following the "Build with CMake instructions here": https://github.com/google/googletest/blob/main/googletest/README.md

# Running the Code

First, make the code via the following commands:

    mkdir build
    cd build
    cmake ..
    make # or 'cmake --build .'
    ./ParallelQuantLib
