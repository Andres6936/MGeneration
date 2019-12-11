// Only include file once
#pragma once

#include "Player.h"

constexpr unsigned short MAP_HEIGHT = 1000;

constexpr unsigned short MAP_WIDTH = 1000;

class World
{

public:

	int height; /* The height of the world map */
	int width;  /* The width of the world map */
	int y_pos;  /* Player y position */
	int x_pos;  /* Player x position */
	char map[1000 * 1000];

	int getIndex(int x, int y);

public:

	char getGlyph(int x, int y);

	void setGlyph(int x, int y, char glyph);

};

World loadWorld(const char* filename);

World newWorld(int height, int width, int walks, int steps, Player* player);