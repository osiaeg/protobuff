cmake_minimum_required(VERSION 3.5)
project(protobuf_parser)

set(CMAKE_CXX_STANDARD 20)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS protos/wrappermessage.proto)

add_executable(parser 
    main.cpp
    ${PROTO_HDRS}
    ${PROTO_SRCS})
target_link_libraries(parser ${Protobuf_LIBRARIES})
target_include_directories(parser PUBLIC third_party)
target_include_directories(parser PUBLIC protobuf_parser)
exec_program(parser)
