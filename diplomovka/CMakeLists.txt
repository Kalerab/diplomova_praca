cmake_minimum_required(VERSION 3.8)
project(diplomovka)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH "/home/rasto/Qt/5.12.1/gcc_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SOURCE_FILES main.cpp common.cpp common.h compute.cpp compute.h graphseparator.cpp graphseparator.h mainprogram.cpp
        mainprogram.h mainwindow.cpp mainwindow.h mainwindow.ui chordlesscycles.cpp chordlesscycles.h scanner.cpp scanner.h
        findpermutation.cpp findpermutation.h cyclepermutation.cpp cyclepermutation.h)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)
add_executable(diplomovka ${SOURCE_FILES})

target_link_libraries(diplomovka Qt5::Widgets)
target_link_libraries(diplomovka Qt5::Quick)
target_link_libraries(diplomovka Qt5::Widgets)