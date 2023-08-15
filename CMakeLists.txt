cmake_minimum_required(VERSION 3.21)
project(ex4_orin1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex4_orin1
        Activation.h
        Dense.h
        main.cpp
        Matrix.cpp
        Matrix.h
        MlpNetwork.h
        Activation.cpp
        Dense.cpp
        MlpNetwork.cpp)
