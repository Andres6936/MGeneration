
#include <cstdio>
#include <cstdlib>

#include "BearLibTerminal.hpp"
#include "World.h"
#include "Player.h"
#include "Vector.h"
#include "EDirection.h"

EDirection getRandomDirection()
{
	int comodin = 1 + rand() % 4;

	if (comodin == 1)
	{
		return EDirection::NORTH;
	}
	else if (comodin == 2)
	{
		return EDirection::WEST;
	}
	else if (comodin == 3)
	{
		return EDirection::EAST;
	}
	else if (comodin == 4)
	{
		return EDirection::SOUTH;
	}
}

World loadWorld(const char* filename)
{
	FILE* stream = fopen(filename, "r");

	if (stream == nullptr)
	{
		puts("Error while reading (open) file");
		exit(EXIT_FAILURE);
	}

	World newWorld = World(1000, 1000);

	int character;
	int row = 0;
	int column = 0;

	while ((character = fgetc(stream)) != EOF)
	{
		if (character == '\n')
		{
			row++;
			column = 0;
		}
		else
		{
			newWorld.setGlyph(row, column, (char)character);
			column++;
		}
	}

	fclose(stream);

	return newWorld;
}

World newWorld(int height, int width, int walks, int steps, Player* player)
{
	// Generate an seed for new map.
	//srand( time(NULL));

	World newWorld = World(MAP_WIDTH, MAP_HEIGHT);

	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			newWorld.setGlyph(x, y, '#');
		}
	}

	Vector2D* freeCells = new Vector2D[walks * steps];

	int counter = 0;

	for (int i = 0; i < walks; ++i)
	{
		int y, x;
		y = rand() % height;
		x = rand() % width;
		for (int j = 0; j < steps; ++j)
		{
			EDirection direction = getRandomDirection();
			switch (direction)
			{
			case EDirection::NORTH:
				if ((y - 1) > 1)
				{
					newWorld.setGlyph(--y, x, '.');
					freeCells[counter].y = y;
					freeCells[counter].x = x;
					counter++;
				}
				break;
			case EDirection::EAST:
				if ((x + 1) < width - 1)
				{
					newWorld.setGlyph(y, ++x, '.');
					freeCells[counter].y = y;
					freeCells[counter].x = x;
					counter++;
				}
				break;
			case EDirection::WEST:
				if ((x - 1) > 1)
				{
					newWorld.setGlyph(y, --x, '.');
					freeCells[counter].y = y;
					freeCells[counter].x = x;
					counter++;
				}
				break;
			case EDirection::SOUTH:
				if ((y + 1) < height - 1)
				{
					newWorld.setGlyph(++y, x, '.');
					freeCells[counter].y = y;
					freeCells[counter].x = x;
					counter++;
				}
				break;
			}
		}
	}

	Vector2D coodinatePlayerRandom = freeCells[rand() % counter];

	player->x = coodinatePlayerRandom.x;
	player->y = coodinatePlayerRandom.y;

	free(freeCells);
	return newWorld;
}

int World::getIndex(int x, int y)
{
	return (y * width) + x;
}

char World::getGlyph(int x, int y)
{
	return map[getIndex(x, y)];
}

void World::setGlyph(int x, int y, char glyph)
{
	map[getIndex(x, y)] = glyph;
}

World::World(int width, int height)
{
	this->width = width;
	this->height = height;
	this->map = new char[width * height];
}

World::World()
{
	width = 0;
	height = 0;
}

