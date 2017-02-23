cmake_minimum_required(VERSION 3.6)
project(Splay_Tree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BinaryNode.h SplayTree.h)
add_executable(Splay_Tree ${SOURCE_FILES})
