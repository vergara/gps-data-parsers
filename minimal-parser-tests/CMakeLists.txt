cmake_minimum_required (VERSION 2.6)
project (minimal-parser-tests)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g " )

include_directories(../status)

add_library(minimalparser ../minimal-parser/minimal-parser.cpp)
add_library(parserimpl ../minimal-parser/parser-impl.cpp)

add_executable(minimal-parser-tests minimal-parser-tests.cpp)

configure_file(test-data-aligned.txt test-data-aligned.txt COPYONLY)
configure_file(test-data-not-aligned.txt test-data-not-aligned.txt COPYONLY)

target_link_libraries(minimal-parser-tests CppUTest minimalparser parserimpl)

