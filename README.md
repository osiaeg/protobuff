# 417-cpp-protobuf

## Installation

Download protobuf [protobuf](https://github.com/protocolbuffers/protobuf/releases/tag/v21.12)

Run this command
```
tar xvf v21.12
cd protobuf-3.21.12/cmake
mkdir build
cmake -B build -DCMAKE_CXX_STANDARD=14
cmake --build build
cd build
sudo make install
```

To run a program and tests
```
./run.sh
```
