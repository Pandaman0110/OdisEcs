cmake_minimum_required(VERSION 3.28)
project(OdisECS)

set(CMAKE_CXX_STANDARD 23)

add_executable(OdisECS main.cpp
        world.hpp
        archetype.hpp
        entity.hpp
        type_id.hpp
        component.hpp
)
