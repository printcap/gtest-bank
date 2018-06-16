cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_CXX_STANDARD 11)

enable_testing()
find_package(GTest REQUIRED)

include(GoogleTest)
add_executable(bank_test bank_test.cpp account_test.cpp)
target_link_libraries(bank_test GTest::GTest GTest::Main)

gtest_discover_tests(bank_test)