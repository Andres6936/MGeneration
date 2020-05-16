// Design by Joan Andrés.

#include <BearLibTerminal/BearLibTerminal.hpp>
#include "Scene/StartScene.hpp"

Gen::StartScene::StartScene(std::shared_ptr<Renderer>& _renderer)
{
	this->renderer = _renderer;
}

void Gen::StartScene::draw()
{
	renderer->writeText(1, 1, "Welcome to MGeneration");
	renderer->writeText(1, 2, "Select a option");
	renderer->writeText(1, 4, "a) Generate map");
	renderer->writeText(1, 5, "b) Exit of app");
	renderer->refresh();

	while (true)
	{
		if (renderer->getKeyPressed() == TK_B) return;
		if (renderer->getKeyPressed() == TK_A) return;
	}
}
