cmake_minimum_required(VERSION 3.5)
project(protobuf_parser)

set(CMAKE_CXX_STANDARD 20)

find_package(Protobuf REQUIRED)

add_subdirectory(protobuf_parser)

add_executable(parser main.cpp)

target_link_libraries(parser PUBLIC MessageParser)
target_include_directories(parser PUBLIC
    "${PROJECT_SOURCE_DIR}/protobuf_parser"
    "${PROJECT_SOURCE_DIR}/third_party")


