cmake_minimum_required (VERSION 2.6)
project (minimal-parser-tests)

set_source_files_properties(../minimal-parser/minimal-parser.c PROPERTIES LANGUAGE CXX )
set_source_files_properties(../minimal-parser/parser-impl/parser-impl.c PROPERTIES LANGUAGE CXX )

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g " )

add_library(minimalparser ../minimal-parser/minimal-parser.c)
add_library(parser-impl ../minimal-parser/parser-impl/parser-impl.c)

add_executable(minimal-parser-tests minimal-parser-tests.cpp)

configure_file(test-data-aligned.txt test-data-aligned.txt COPYONLY)
configure_file(test-data-not-aligned.txt test-data-not-aligned.txt COPYONLY)

target_link_libraries(minimal-parser-tests CppUTest minimalparser parser-impl)

