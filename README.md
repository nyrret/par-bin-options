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

# Stencil Copmutations

If using the cache-optimized stencil code, ensure to update the L1, L2, and L3 cache capacities defined in binomial.h to reflect your machine.  These should be reported in terms of the number of 8-byte doubles able to be fit into the chace.
