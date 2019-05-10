cmake_minimum_required(VERSION 3.8)
project(negatsub)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -pthread")

set(SOURCE_FILES main.cpp common.cpp common.h graphseparator.cpp graphseparator.h
        chordlesscycles.cpp chordlesscycles.h scanner.cpp scanner.h
        findpermutation.cpp findpermutation.h findnegators.cpp findnegators.h)

add_executable(negatsub ${SOURCE_FILES})
