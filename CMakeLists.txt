cmake_minimum_required(VERSION 3.10)
project(false_sharing)
enable_language(C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(false_sharing main.cpp)

enable_testing()

# Small workload: quick tests
add_test(NAME test_1 COMMAND false_sharing --iter 1000000 --runs 3)
add_test(NAME test_2 COMMAND false_sharing --iter 1000000 --runs 5)

# Medium workload: moderate tests
add_test(NAME test_3 COMMAND false_sharing --iter 100000 --runs 3)
add_test(NAME test_4 COMMAND false_sharing --iter 500000 --runs 5)
add_test(NAME test_5 COMMAND false_sharing --iter 120000 --runs 12)

# Large workload: stress tests
add_test(NAME test_6 COMMAND false_sharing --iter 100000000 --runs 3)
add_test(NAME test_7 COMMAND false_sharing --iter 100000000 --runs 5)
add_test(NAME test_8 COMMAND false_sharing --iter 300000000 --runs 10)