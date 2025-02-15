cmake_minimum_required(VERSION 3.10)
project(DiseaseSimulation VERSION 0.1.0 LANGUAGES C CXX)

add_executable(DiseaseSimulation disease.cpp person.cpp population.cpp proj.cpp simulator.cpp)

