cmake_minimum_required(VERSION 3.18.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(thimble)

include(CTest)
enable_testing()

add_executable(
  thimble 
  main.cpp 
  src/lexer.cpp
)

add_subdirectory(googletest)
add_subdirectory(example)

target_link_libraries(example PUBLIC example_lib gtest gtest_main gmock gmock_main)

include(GoogleTest) # To use gtest_discover_tests

gtest_discover_tests(example) # Runs GTest with CTest