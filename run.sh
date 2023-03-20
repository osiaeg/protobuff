#!/bin/bash
cmake -B build
cmake --build build --parallel --config Release && clear
./build/src/parser
