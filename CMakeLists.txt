# vim: ft=cmake:et:ts=4:ff=unix:fenc=utf-8:
cmake_minimum_required(VERSION 3.0.2)
set(pname evq_test)
project(${pname} C)

if (UNIX)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
endif ()

add_executable(${pname} main.c evqueue.c)
target_link_libraries(${pname} ev)

