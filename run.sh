#!/bin/bash
rm -rf build/*
cmake -B build -DBUILD_TESTING=OFF
cmake --build build -j 8
#./build/src/parser
