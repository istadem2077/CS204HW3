cmake_minimum_required(VERSION 3.30)
project(CS204HW3)

set(CMAKE_CXX_STANDARD 17)

add_executable(CS204HW3 HW3main.cpp
        TabsDLL.cpp
        TabsDLL.h
        DynPageStack.cpp
        DynPageStack.h
)
