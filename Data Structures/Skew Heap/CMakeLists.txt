cmake_minimum_required(VERSION 3.6)
project(Skew_Heap)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BinaryNode.h SkewHeap.h)
add_executable(Skew_Heap ${SOURCE_FILES})