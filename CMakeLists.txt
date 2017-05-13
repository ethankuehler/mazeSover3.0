cmake_minimum_required(VERSION 3.7)
project(MazeSolver)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        Main.cpp
        Solver.h
        Solver.cpp
        Node.h
        Node.cpp
        FileName.h
        FileName.cpp
        easyBMP/EasyBMP.h
        easyBMP/EasyBMP.cpp
        easyBMP/EasyBMP_VariousBMPutilities.h
        easyBMP/EasyBMP_DataStructures.h
        easyBMP/EasyBMP_BMP.h
        )

add_executable(mazeSover3_0 ${SOURCE_FILES})