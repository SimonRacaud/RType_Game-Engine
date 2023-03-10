##
## EPITECH PROJECT, 2021
## Indie Studio
## File description:
## gameEngine cmake
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME gameEngine)

project(${NAME} VERSION 0.1 LANGUAGES CXX)

## INCLUDES
include_directories(
        ./include
        ./src/
)

## SOURCES
set(SRCS
    # Exception
    src/Exception/BasicException.cpp

    src/ComponentManager/ComponentManager.cpp
    src/ComponentTypeRegister/ComponentTypeRegister.hpp

    src/EntityManager/EntityManager.cpp

    src/EntityRegister/EntityRegister.cpp
    src/EntityRegister/EntityBlock.cpp

    src/NetworkIdRegister/NetworkIdRegister.cpp

    src/SystemManager/SystemManager.cpp

    src/AbstractSystem/AbstractSystem.hpp
    src/AbstractScene/AbstractScene.hpp

    src/SceneManager/SceneManager.cpp

    src/Engine/GameEngine.cpp
    src/Engine/EngineFactory.cpp

    src/Utils/display.cpp
    src/Utils/SignalManager.cpp
    src/Components/ScoreComponent.hpp
    src/Components/NumberComponent.hpp
    src/Components/EntityLinkComponent.hpp
    src/Components/SizeComponent.hpp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
add_library(${NAME} SHARED ${SRCS})

if (WIN32)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    target_compile_options(${NAME} PRIVATE)
else ()
    target_compile_options(${NAME} PRIVATE -Wall -Wextra -fPIC)
endif ()