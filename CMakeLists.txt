cmake_minimum_required(VERSION 3.8)
project(bst)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        bst.cpp
        bst.h
        main.cpp
        test.txt
        test2.txt TTTree.cpp TTTree.h)

add_executable(bst ${SOURCE_FILES} TTTree.cpp TTTree.h)