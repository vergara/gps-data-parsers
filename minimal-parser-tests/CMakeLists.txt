cmake_minimum_required (VERSION 2.6)
project (minimal-parser-tests)

set_source_files_properties(../minimal-parser/minimal-parser.c PROPERTIES LANGUAGE CXX )

add_library(minimalparser ../minimal-parser/minimal-parser.c)

add_executable(minimal-parser-tests minimal-parser-tests.cpp)

configure_file(test-data-aligned.txt test-data-aligned.txt COPYONLY)
configure_file(test-data-not-aligned.txt test-data-not-aligned.txt COPYONLY)

target_link_libraries(minimal-parser-tests CppUTest minimalparser)

