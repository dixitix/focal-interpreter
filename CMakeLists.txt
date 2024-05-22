cmake_minimum_required(VERSION 3.24)
project(focal_interpreter)

set(CMAKE_CXX_STANDARD 14)

include_directories(errors)
include_directories(parser)
include_directories(scanner)

add_executable(focal_interpreter
        errors/error.cpp
        errors/error.h
        parser/parser.cpp
        parser/parser.h
        parser/parser_ext.h
        scanner/scanner.cpp
        scanner/scanner_data.h
        scanner/scanner_ext.h
        scanner/scanner_local.h
        scanner/scanner_type.h
        scanner/testout.cpp
        main.cpp)
