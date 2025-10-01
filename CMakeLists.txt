cmake_minimum_required(VERSION 3.26)
project(Huffman)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

# Programa principal
add_executable(Huffman
        src/main.cpp
        src/huffman_encoder.cpp
)

# Test 1
add_executable(Test1
        tests/test_case_1.cpp
        src/huffman_encoder.cpp
)

# Test 2
add_executable(Test2
        tests/test_case_2.cpp
        src/huffman_encoder.cpp
)

# Test 3
add_executable(Test3
        tests/test_case_3.cpp
        src/huffman_encoder.cpp
)
