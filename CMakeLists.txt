cmake_minimum_required(VERSION 3.10)

enable_testing()
find_package(GTest REQUIRED)

add_executable(bank_test bank_test.cpp account_test.cpp)
target_compile_features(bank_test PRIVATE cxx_auto_type cxx_variadic_templates)
target_link_libraries(bank_test GTest::GTest GTest::Main)

gtest_discover_tests(bank_test)
