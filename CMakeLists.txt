cmake_minimum_required(VERSION 3.12)
project(Nmail_server)

set(CMAKE_CXX_STANDARD 14)

add_executable(Nmail_server main.cpp server.c)