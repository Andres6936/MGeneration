#include <cstdio>
#include <cstdlib>

#include "BearLibTerminal.hpp"
#include "World.h"
#include "Player.h"
#include "Vector.h"
#include "EDirection.h"
#include "DrawDungeon.h"

const unsigned int walks = 1000;

const unsigned int steps = 2500;

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
