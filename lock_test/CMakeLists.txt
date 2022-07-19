cmake_minimum_required(VERSION 3.17)
project(lock_test)

set(CMAKE_CXX_STANDARD 14)
find_package(Threads)
add_executable(lock_test main.cpp)
target_link_libraries (lock_test ${CMAKE_THREAD_LIBS_INIT})
