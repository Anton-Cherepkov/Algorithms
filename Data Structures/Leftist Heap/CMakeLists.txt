cmake_minimum_required(VERSION 3.6)
project(Leftist_Heap)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BinaryNode.h LeftistHeap.h)
add_executable(Leftist_Heap ${SOURCE_FILES})