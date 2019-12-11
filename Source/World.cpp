// Relax, You can deleted this sentence
#pragma clang diagnostic push
// Relax, You can deleted this sentence
#pragma ide diagnostic ignored "cert-msc30-c"

#include <cstdio>
#include <cstdlib>
#include <vector>

#include "World.h"
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

World::World()
{
	width = 0;
	height = 0;
}

World::World(int width, int height)
{
	this->width = width;
	this->height = height;
	this->map = new char[width * height];
}

World::World(int width, int height, int walks, int steps)
{
	this->width = width;
	this->height = height;

	map = new char[width * height];

	for (int i = 0; i < width * height; i++)
	{
		map[i] = '#';
	}

	std::vector <Vector2D> freeCells;
	freeCells.reserve(walks * steps);

	int counter = 0;

	for (int i = 0; i < walks; ++i)
	{
		int y = rand() % height;
		int x = rand() % width;

		for (int j = 0; j < steps; ++j)
		{
			EDirection direction = getRandomDirection();

			switch (direction)
			{
			case EDirection::NORTH:
				if ((y - 1) > 1)
				{
					setGlyph(--y, x, '.');
					freeCells[counter].y = y;
					freeCells[counter].x = x;
					counter++;
				}
				break;
			case EDirection::EAST:
				if ((x + 1) < width - 1)
				{
					setGlyph(y, ++x, '.');
					freeCells[counter].y = y;
					freeCells[counter].x = x;
					counter++;
				}
				break;
			case EDirection::WEST:
				if ((x - 1) > 1)
				{
					setGlyph(y, --x, '.');
					freeCells[counter].y = y;
					freeCells[counter].x = x;
					counter++;
				}
				break;
			case EDirection::SOUTH:
				if ((y + 1) < height - 1)
				{
					setGlyph(++y, x, '.');
					freeCells[counter].y = y;
					freeCells[counter].x = x;
					counter++;
				}
				break;
			}
		}
	}
}

int World::getIndex(int x, int y) const
{
	return (y * width) + x;
}

char World::getGlyph(int x, int y) const
{
	return map[getIndex(x, y)];
}

void World::setGlyph(int x, int y, char glyph)
{
	map[getIndex(x, y)] = glyph;
}

int World::getWidth() const
{
	return width;
}

int World::getHeight() const
{
	return height;
}