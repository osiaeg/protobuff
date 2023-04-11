#!/bin/bash
#rm -rf build/*
cmake -B build -DBUILD_TESTING=ON
cmake --build build -j 8
cd build && ctest && cd ..
#./build/src/parser
