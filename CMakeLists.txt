cmake_minimum_required(VERSION 3.10)
project(oware)

set(CMAKE_CXX_STANDARD 17)

add_executable(oware src/main.cpp src/Board.cpp include/Board.h src/Player.cpp include/Player.h)