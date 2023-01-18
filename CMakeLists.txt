cmake_minimum_required(VERSION 3.24)
project(ConwaysRidiculousLife)

set(CMAKE_CXX_STANDARD 17)

add_executable(ConwaysRidiculousLife main.cpp IO/LifeIo.h GameOf/Life.cpp GameOf/Life.h)
