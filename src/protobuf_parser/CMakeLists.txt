protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ../protos/wrappermessage.proto)
add_library( Helpers helpers.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_include_directories(Helpers PUBLIC "${PROJECT_BINARY_DIR}/protobuf_parser")
