cmake_minimum_required(VERSION 3.10)
project(DiseaseSimulation VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB SRC "src/*.cpp")

add_executable(DiseaseSimulation ${SRC})

