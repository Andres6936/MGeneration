#include <BearLibTerminal/BearLibTerminal.hpp>
#include "World.h"
#include "Player.h"
#include "DrawDungeon.h"

using namespace Gen;

const unsigned int walks = 1000;

const unsigned int steps = 2500;

int main(int argc, char* argv[])
{
	// Initial map.
	World world = World(MAP_HEIGHT, MAP_WIDTH, walks, steps);
	Player player;

	// We assume that the second parameter points to a file that contains
	// a map already generated.
	if (argc == 2)
	{
		world = Gen::loadWorld(argv[1]);
		player = Player(60, 30);
	}
	else
	{
		// If there are not argument, use the initial map.
		player.setPositionRandomAtMap(world);
	}

	TerminalOpen();
	TerminalSet("terminal: encoding=437");
	TerminalSet("window: size=80x25, cellsize=auto, title=MGeneration");

	bool running = true;

	TerminalClear();
	Gen::DrawDungeon(world, player);
	TerminalRefresh();

	// Main Loop
	while (running)
	{
		// Key pressed for user
		int key = TerminalRead();

		// The user close the window or app
		if (key == TK_CLOSE)
		{
			running = false;
		}

		// Handle events
		player.handlerEventPlayer(key);

		// Clear, Draw and Refresh
		TerminalClear();
		Gen::DrawDungeon(world, player);
		TerminalRefresh();
	}

	TerminalClose();

	return 0;
}
