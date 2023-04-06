add_executable(test_helpers Test_Helpers.cpp)
target_link_libraries(test_helpers GTest::gtest_main Helpers)

include(GoogleTest)
gtest_discover_tests(test_helpers)
