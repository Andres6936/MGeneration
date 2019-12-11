// Only include file once
#pragma once

#include "Player.h"

constexpr unsigned short MAP_HEIGHT = 1000;

constexpr unsigned short MAP_WIDTH = 1000;

class World
{

private:

	int height; // The height of the world map
	int width;  // The width of the world map

	char* map = nullptr;

	[[nodiscard]] int getIndex(int x, int y) const;

public:

	World();

	World(int width, int height);

	World(int width, int height, int walks, int steps);

	~World();

	[[nodiscard]] char getGlyph(int x, int y) const;

	[[nodiscard]] int getWidth() const;

	[[nodiscard]] int getHeight() const;

	void setGlyph(int x, int y, char glyph);

};

World loadWorld(const char* filename);