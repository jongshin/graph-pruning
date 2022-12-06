#!/bin/bash

# Create build-directory
# mkdir build

# Move into the build-directory
cd build

# Run CMake to create a Makefile
cmake ../ -DMYLIB_BUILD_WARNINGS=ON
# cmake ../ -DCMAKE_BUILD_TYPE=release

# Make the Makefile using two threads
make

# Move the executable to the bin-directory
# mv TestMyLib.out ../bin

cd ..
./runTests.sh