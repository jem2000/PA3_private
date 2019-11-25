cmake_minimum_required(VERSION 3.15)
project(pa3)

set(CMAKE_CXX_STANDARD 98)

add_executable(pa3 main.cpp Point2D.cpp Point2D.h Vector2D.cpp Vector2D.h GameObject.cpp GameObject.h Building.cpp Building.h PokemonCenter.cpp PokemonCenter.h PokemonGym.cpp PokemonGym.h Pokemon.cpp Pokemon.h Model.cpp Model.h GameCommand.cpp GameCommand.h View.cpp View.h)