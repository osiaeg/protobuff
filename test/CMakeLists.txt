add_executable(test_helpers Test_Helpers.cpp)
target_link_libraries(test_helpers Helpers GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_helpers)
