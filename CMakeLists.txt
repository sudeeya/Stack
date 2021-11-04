cmake_minimum_required(VERSION 3.5)

project(stack_project NONE)

enable_language(CXX)

add_compile_options(-Wpedantic -Wall -Wextra -Werror -Wshadow)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(stack)