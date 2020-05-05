cmake_minimum_required(VERSION 3.16)
project(meta)

set(CMAKE_CXX_STANDARD 17)

include_directories(./)

add_subdirectory(third-party/googletest)
add_subdirectory(tests)