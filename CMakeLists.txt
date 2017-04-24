cmake_minimum_required(VERSION 3.0)
project(connect4players)
set(CMAKE_CXX_STANDARD 11)

set(jklepp_ExamplePlayer
        jklepp_ExamplePlayer/ExamplePlayer.h
        jklepp_ExamplePlayer/ExamplePlayer.cpp)

set(jklepp_ForcedOrGaussPlayer
        jklepp_ForcedOrGaussPlayer/ForcedOrGaussPlayer.h
        jklepp_ForcedOrGaussPlayer/ForcedOrGaussPlayer.cpp)

add_library(connect4players STATIC
        Player.h PlayerRegistry.cpp PlayerRegistry.h
        ${jklepp_ExamplePlayer}
        ${jklepp_ForcedOrGaussPlayer}
)