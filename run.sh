#!/bin/bash
#rm -rf build/*
cmake -B build -DBUILD_TESTING=ON
cmake --build build -j 8
./build/src/parser
cd build && ctest && cd ..
