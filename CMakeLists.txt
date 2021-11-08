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

if(ADD_SANITIZERS)
  target_compile_options(${PROJECT_NAME} PUBLIC -fsanitize=address -g)
  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-fsanitize=address")
endif()

add_custom_target(
  run_${PROJECT_NAME}
  COMMAND ./${PROJECT_NAME}
)

add_dependencies(run_${PROJECT_NAME} ${PROJECT_NAME})

add_subdirectory(stack)