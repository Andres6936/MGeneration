// Design by Joan Andrés.

#include "Scene/PlayScene.hpp"

using namespace Gen;

PlayScene::PlayScene(std::shared_ptr<Renderer>& _renderer) : player(std::ref(world))
{
	this->renderer = _renderer;

	const unsigned int WALKS = 1000;
	const unsigned int STEPS = 2500;

	// If there are not argument, generate a new map.
	this->world = World(MAP_HEIGHT, MAP_WIDTH);
	this->world.generateByAutomateCellular(WALKS, STEPS);

}

void PlayScene::draw()
{
	world.draw(renderer, player);
}

void PlayScene::clear()
{
	renderer->clear();
}

void PlayScene::update()
{
	renderer->refresh();
}

NextScene PlayScene::event()
{
	// Key pressed for user
	int key = renderer->getKeyPressed();

	// The user close the window or app
	if (key == TK_CLOSE)
	{
		return NextScene::Exit;
	}

	player.handlerEventPlayer(key);

	return NextScene::None;
}
