cmake_minimum_required(VERSION 3.12)
project(Zork)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(rapidxml-1.13)

add_executable(Zork
        rapidxml-1.13/rapidxml.hpp
        rapidxml-1.13/rapidxml_iterators.hpp
        rapidxml-1.13/rapidxml_print.hpp
        rapidxml-1.13/rapidxml_utils.hpp
        container.cpp
        container.hpp
        creature.cpp
        creature.hpp
        attack.cpp
        attack.hpp
        executioner.hpp
        item.cpp
        item.hpp
        trigger.cpp
        trigger.hpp
        room.cpp
        room.hpp
        #header.cpp
        main.cpp
        header.hpp)
