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
	width = 80;
	height = 24;
}

World::World(const int width, const int height) noexcept
{
	this->width = width;
	this->height = height;
	resize(width * height);
}

// Methods

void World::draw(std::shared_ptr<Renderer>& renderer, const Player& player)
{
	// WINDOW_WIDTH = 80;
	// WINDOW_HEIGHT = 25;

	int startX = player.getX() - (80 / 2);
	int startY = player.getY() - (25 / 2);

	if (player.getX() < 80 / 2)
	{
		startX = 0;
	}
	else if (player.getX() >= MAP_WIDTH - (80 / 2))
	{
		startX = MAP_WIDTH - 80;
	}

	if (player.getY() < 25 / 2)
	{
		startY = 0;
	}
	else if (player.getY() >= MAP_HEIGHT - (25 / 2))
	{
		startY = MAP_HEIGHT - 25;
	}

	for (int x = 0; x < 80; x++)
	{
		for (int y = 0; y < 25; y++)
		{
			renderer->setBackgroundColor("white");
			renderer->write(x, y, getGlyph(x + startX, y + startY));
		}
	}

	renderer->setBackgroundColor("orange");
	renderer->write(player.getX() - startX, player.getY() - startY, '@');
}

// Getters

int World::getGlyph(int x, int y) const
{
	return at((y * width) + x).getCode();
}

int World::getWidth() const
{
	return width;
}

int World::getHeight() const
{
	return height;
}

// Setters

void World::setGlyph(int x, int y, int glyph)
{
	at((y * width) + x).setCode(glyph);
}

void World::generateByAutomateCellular(const int walks, const int steps)
{
	// Fill the actual map
	std::fill(begin(), end(), '#');

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
