cmake_minimum_required(VERSION 3.5)

project(stack_project NONE)

enable_language(CXX)

add_compile_options(-Wpedantic -Wall -Wextra -Werror -Wshadow)

file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h)
add_custom_target(
  clang_format
  COMMAND clang-format -i ${ALL_SOURCE_FILES}
)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(stack)