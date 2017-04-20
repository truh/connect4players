cmake_minimum_required(VERSION 3.0)
project(connect4players)
set(CMAKE_CXX_STANDARD 11)

set(PLAYER_HEADERS jklepp_ExamplePlayer/ExamplePlayer.h)
set(PLAYER_SOURCES jklepp_ExamplePlayer/ExamplePlayer.cpp)

add_library(connect4players STATIC Player.h PlayerRegistry.cpp PlayerRegistry.h ${PLAYER_HEADERS} ${PLAYER_SOURCES})