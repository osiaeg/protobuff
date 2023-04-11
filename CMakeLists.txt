cmake_minimum_required(VERSION 3.2)

project(length_profixed_protobuf LANGUAGES C CXX)

add_subdirectory(src)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
if(BUILD_TESTING)
    add_subdirectory(test)
endif()
