cmake_minimum_required(VERSION 3.15)

project(QtRestClient)

find_package(Qt5 COMPONENTS Core Network REQUIRED )

add_subdirectory( src )
