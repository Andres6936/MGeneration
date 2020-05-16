CMAKE_MINIMUM_REQUIRED(VERSION 3.14 FATAL_ERROR)

PROJECT(MGeneration VERSION 0.1 LANGUAGES CXX)

INCLUDE(CMakeModules/CPM.cmake)

### Add dependencies via CPM
# Add BearLibTerminal like dependency
CPMADDPACKAGE(
        NAME BearLibTerminal
        GITHUB_REPOSITORY Andres6936/BearLibTerminal
        VERSION 2020.4
)

INCLUDE_DIRECTORIES(Include)

ADD_EXECUTABLE(MGeneration
        Source/Main.cpp
        Source/Cell.cpp
        Source/World.cpp
        Source/Player.cpp
        Source/Render/Terminal.cpp Source/Scene/StartScene.cpp)

SET_TARGET_PROPERTIES(MGeneration PROPERTIES CXX_STANDARD 17)

# Load and link the library BearLibTerminal
TARGET_LINK_LIBRARIES(MGeneration PRIVATE BearLibTerminal)