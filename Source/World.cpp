// Relax, You can deleted this sentence
#pragma clang diagnostic push
// Relax, You can deleted this sentence
#pragma ide diagnostic ignored "cert-msc30-c"

#include <cstdio>
#include <cstdlib>
#include <vector>

#include "World.h"
#include "Vector.h"
#include "Direction.h"

using namespace Gen;

Direction getRandomDirection()
{
	int comodin = 1 + rand() % 4;

	if (comodin == 1)
	{
		return Direction::North;
	}
	else if (comodin == 2)
	{
		return Direction::West;
	}
	else if (comodin == 3)
	{
		return Direction::East;
	}
	else if (comodin == 4)
	{
		return Direction::South;
	}
	else
	{
		// For preference of universe
		return Direction::West;
	}
}

World::World(const char* filename) noexcept
{
	FILE* stream = fopen(filename, "r");

	if (stream == nullptr)
	{
		puts("Error while reading (open) file");
		// Generate a empty map
		this->width = 0;
		this->height = 0;
		// Exit of constructor
		return;
	}

	this->width = 1000;
	this->height = 1000;
	resize(width * height);

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
			setGlyph(row, column, (char)character);
			column++;
		}
	}

	fclose(stream);
}

World::World() noexcept
{
	width = 0;
	height = 0;
}

World::World(const int width, const int height) noexcept
{
	this->width = width;
	this->height = height;
	resize(width * height);
}

World::World(const int width, const int height, const int walks, const int steps) noexcept
{
	this->width = width;
	this->height = height;

	resize(width * height);

	for (int i = 0; i < width * height; i++)
	{
		at(i) = '#';
	}

	std::vector<Vector2D> freeCells;
	freeCells.reserve(walks * steps);

	int counter = 0;

	for (int i = 0; i < walks; ++i)
	{
		int y = rand() % height;
		int x = rand() % width;

		for (int j = 0; j < steps; ++j)
		{
			Direction direction = getRandomDirection();

			switch (direction)
			{
			case Direction::North:
				if ((y - 1) > 1)
				{
					setGlyph(--y, x, '.');
					freeCells[counter].y = y;
					freeCells[counter].x = x;
					counter++;
				}
				break;
			case Direction::East:
				if ((x + 1) < width - 1)
				{
					setGlyph(y, ++x, '.');
					freeCells[counter].y = y;
					freeCells[counter].x = x;
					counter++;
				}
				break;
			case Direction::West:
				if ((x - 1) > 1)
				{
					setGlyph(y, --x, '.');
					freeCells[counter].y = y;
					freeCells[counter].x = x;
					counter++;
				}
				break;
			case Direction::South:
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

char World::getGlyph(int x, int y) const
{
	return at((y * width) + x);
}

void World::setGlyph(int x, int y, char glyph)
{
	at(y * width + x) = glyph;
}

int World::getWidth() const
{
	return width;
}

int World::getHeight() const
{
	return height;
}