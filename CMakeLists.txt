cmake_minimum_required(VERSION 3.17)
project(all_tymrazemnapewno)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/include/*")
file(GLOB_RECURSE SOURCES  "${CMAKE_SOURCE_DIR}/src/*")

include_directories(
        ${CMAKE_HOME_DIRECTORY}/include
)

add_executable(all_tymrazemnapewno src/main.cpp  ${HEADERS} ${SOURCES})

