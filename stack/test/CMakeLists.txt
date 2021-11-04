cmake_minimum_required(VERSION 3.5)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(stack_tests tests.cpp)
target_link_libraries(stack_tests PUBLIC GTest::GTest GTest::Main)

add_custom_target(run_stack_tests
  COMMAND ./stack_tests
)

add_dependencies(run_stack_tests stack_tests)