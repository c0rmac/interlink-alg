cmake_minimum_required(VERSION 3.29)
project(interlink_alg_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(interlink_alg_cpp main.cpp
        interlink_alg.cpp
        interlink_alg.hpp
        generate_test_data.cpp
        generate_test_data.hpp)
