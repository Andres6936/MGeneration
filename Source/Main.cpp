#include <memory>
#include <iostream>

#include "World.h"
#include "Player.h"
#include "Render/Renderer.hpp"
#include "Render/Terminal.hpp"
#include "Scene/StartScene.hpp"

using namespace Gen;

int main(int argc, char* argv[])
{
	const unsigned int WALKS = 1000;
	const unsigned int STEPS = 2500;

	// Initial map.
	World world;

	// We assume that the second parameter points to a file that contains
	// a map already generated.
	if (argc == 2)
	{
		world = World(argv[1]);
	}
	else
	{
		// If there are not argument, generate a new map.
		world = World(MAP_HEIGHT, MAP_WIDTH);
		world.generateByAutomateCellular(WALKS, STEPS);
	}

	Player player = Player(std::ref(world));
	std::shared_ptr<Renderer> renderer = std::make_shared<Terminal>();

	StartScene startScene(renderer);
	startScene.draw();

	bool running = true;

	world.draw(renderer, player);
	renderer->refresh();

	// Main Loop
	while (running)
	{
		// Key pressed for user
		int key = renderer->getKeyPressed();

		// The user close the window or app
		if (key == TK_CLOSE)
		{
			running = false;
		}

		// Handle events
		player.handlerEventPlayer(key);

		// Clear, Draw and Refresh
		renderer->clear();
		world.draw(renderer, player);
		renderer->refresh();
	}
}
