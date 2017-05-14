cmake_minimum_required(VERSION 3.7)
project(MazeSolver)

set(CMAKE_CXX_STANDARD 14)


set(SOURCE_FILES
        Main.cpp
        Node.h
        Node.cpp
        Solver.h
        Solver.cpp
        FileName.h
        FileName.cpp
        easyBMP/EasyBMP.h
        easyBMP/EasyBMP.cpp
        easyBMP/EasyBMP_BMP.h
        easyBMP/EasyBMP_DataStructures.h
        easyBMP/EasyBMP_VariousBMPutilities.h
        )


add_executable(MazeSovler ${SOURCE_FILES})