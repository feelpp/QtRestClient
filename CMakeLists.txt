cmake_minimum_required(VERSION 3.15)

project(QtRestClient)

if ( NOT QT_VERSION_MAJOR )
  find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
endif()
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

add_subdirectory( src )
