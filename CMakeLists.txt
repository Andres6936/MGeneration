CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(MGeneration)
# Find the librarys here
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/Lib)
ADD_EXECUTABLE(MGeneration Main.c
        Source/World.c
        Source/Player.c
        Source/DrawDungeon.c)
TARGET_LINK_LIBRARIES(MGeneration ncurses)
# Load and link the library BearLibTerminal
TARGET_LINK_LIBRARIES(MGeneration BearLibTerminal)