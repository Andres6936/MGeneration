CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(MGeneration)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS "--coverage")

# Find the librarys here
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/Lib)

INCLUDE_DIRECTORIES(Include)

ADD_EXECUTABLE(MGeneration Source/Main.cpp
        Source/World.cpp
        Source/Player.cpp
        Source/DrawDungeon.cpp)

# Load and link the library BearLibTerminal
TARGET_LINK_LIBRARIES(MGeneration BearLibTerminal)