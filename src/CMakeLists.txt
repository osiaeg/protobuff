cmake_minimum_required(VERSION 3.5)
project(protobuf_parser)

set(CMAKE_CXX_STANDARD 20)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(parser main.cpp)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS proto_files/wrappermessage.proto)
add_library(proto ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(parser PUBLIC
        ${Protobuf_LIBRARIES}
        proto)
target_include_directories(parser PUBLIC
        "${PROJECT_SOURCE_DIR}/protobuf_parser"
        )