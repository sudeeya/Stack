cmake_minimum_required(VERSION 3.5)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(stack_tests tests.cpp)
target_link_libraries(stack_tests PUBLIC GTest::GTest GTest::Main)

if(ADD_SANITIZERS)
  target_compile_options(stack_tests PUBLIC -fsanitize=address -g)
  set_target_properties(stack_tests PROPERTIES LINK_FLAGS "-fsanitize=address")
endif()

if(ADD_CLANG_TIDY)
  set_target_properties(stack_tests PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_FLAGS}")
endif()

add_custom_target(
  run_stack_tests
  COMMAND ./stack_tests
)

add_dependencies(run_stack_tests stack_tests)