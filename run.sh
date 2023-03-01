#!/bin/bash
cmake -B build
cmake --build build --parallel --config Release
./build/src/protobuf_parser
