cmake_minimum_required(VERSION 3.5)
project(Qubic)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



add_executable(Qubic main.cpp Player.cpp Cube.cpp Qubic.cpp)
