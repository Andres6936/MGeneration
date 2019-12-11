#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "BearLibTerminal.hpp"
#include "World.h"
#include "Player.h"
#include "Vector.h"
#include "EDirection.h"
#include "DrawDungeon.h"

const unsigned int walks = 1000;

const unsigned int steps = 2500;

World loadWorld(const char* filename)
{
	FILE* stream = fopen(filename, "r");

	if (stream == NULL)
	{
		puts("Error while reading (open) file");
		exit(EXIT_FAILURE);
	}

	World newWorld;

	// NOTE: Deleteme
	newWorld.width = 1000;
	newWorld.height = 1000;

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
			newWorld.map[row][column] = (char)character;
			column++;
		}
	}

	fclose(stream);

	return newWorld;
}

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

World newWorld(int height, int width, int walks, int steps, Player* player)
{
	// Generate an seed for new map.
	//srand( time(NULL));

	World newWorld;

	newWorld.height = MAP_HEIGHT;
	newWorld.width = MAP_WIDTH;

	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			newWorld.map[x][y] = '#';
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
					newWorld.map[--y][x] = '.';
					freeCells[counter].y = y;
					freeCells[counter].x = x;
					counter++;
				}
				break;
			case EDirection::EAST:
				if ((x + 1) < width - 1)
				{
					newWorld.map[y][++x] = '.';
					freeCells[counter].y = y;
					freeCells[counter].x = x;
					counter++;
				}
				break;
			case EDirection::WEST:
				if ((x - 1) > 1)
				{
					newWorld.map[y][--x] = '.';
					freeCells[counter].y = y;
					freeCells[counter].x = x;
					counter++;
				}
				break;
			case EDirection::SOUTH:
				if ((y + 1) < height - 1)
				{
					newWorld.map[++y][x] = '.';
					freeCells[counter].y = y;
					freeCells[counter].x = x;
					counter++;
				}
				break;
			default:
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

int main(int argc, char* argv[])
{
	World world;
	Player player;

	// We assume that the second parameter points to a file that contains
	// a map already generated.
	if (argc == 2)
	{
		world = loadWorld(argv[1]);
		player.x = 60;
		player.y = 30;
	}
	else
	{
		// If there are not argument, generate a new map.
		world = newWorld(MAP_HEIGHT, MAP_WIDTH, walks, steps, &player);
	}

	TerminalOpen();
	TerminalSet("terminal: encoding=437");
	TerminalSet("window: size=80x25, cellsize=auto, title=MGeneration");

	// Key pressed for user
	int key;

	bool running = true;

	TerminalClear();
	DrawDungeon(&world, &player);
	TerminalRefresh();

	// Main Loop
	while (running)
	{
		key = TerminalRead();

		// The user close the window or app
		if (key == TK_CLOSE)
		{
			running = false;
		}

		// Handle events
		handlerEventPlayer(key, &player);

		// Clear, Draw and Refresh
		TerminalClear();
		DrawDungeon(&world, &player);
		TerminalRefresh();
	}

	TerminalClose();

	return 0;
}
