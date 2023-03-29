#!/bin/bash
rm -rf build/*
ls build
cmake -B build
cmake --build build -j 8
./build/src/parser
