cmake_minimum_required(VERSION 3.18.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(thimble)

add_subdirectory(googletest)
include_directories(googletest/googletest/include)

add_executable(
  thimble 
  main.cpp 
  src/lexer.cpp
  src/parser.cpp
)

add_executable(
  tests

  src/lexer.cpp
  src/parser.cpp

  tests/tests.cpp
  tests/lexer.cpp
)

target_link_libraries(tests PRIVATE gtest)