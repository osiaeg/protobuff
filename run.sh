#!/bin/bash
rm -rf build/*
ls build
cmake -B build
cmake --build build --parallel --config Release
./build/parser
