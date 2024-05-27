cmake_minimum_required(VERSION 3.24)
project(CNN)

set(CMAKE_CXX_STANDARD 23)

add_executable(CNN main.cpp Perceptron.cpp Perceptron.h Network.cpp Network.h Image.cpp Image.h Parser.cpp Parser.h)
