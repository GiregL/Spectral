cmake_minimum_required(VERSION 3.16)
project(Spectral)

set(CMAKE_CXX_STANDARD 17)

add_executable(Spectral main.cpp network/ServerSocket.cpp network/ServerSocket.h http/HTTPParser.cpp http/HTTPParser.h http/HTTPMethod.h)

target_link_libraries(Spectral "-lpthread")