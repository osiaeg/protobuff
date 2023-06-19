protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ../proto_files/wrappermessage.proto)
add_library(Helpers helpers.cpp ${PROTO_SRCS} ${PROTO_HDRS})
add_library(MessageParser DelimitedMessagesStreamParser.cpp)
target_link_libraries(Helpers ${Protobuf_LIBRARIES})
target_link_libraries(MessageParser Helpers)

target_include_directories(Helpers PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${PROJECT_BINARY_DIR}/protobuf_parser")
target_include_directories(MessageParser PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${PROJECT_BINARY_DIR}/protobuf_parser")
