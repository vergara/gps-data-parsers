cmake_minimum_required (VERSION 2.6)
project (minimal-parser-tests)

set_source_files_properties(../minimal-parser/minimal-parser.c PROPERTIES LANGUAGE CXX )

add_library(minimalparser ../minimal-parser/minimal-parser.c)

add_executable(minimal-parser-tests minimal-parser-tests.cpp)

target_link_libraries(minimal-parser-tests CppUTest minimalparser)

