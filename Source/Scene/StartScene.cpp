// Design by Joan Andrés.

#include <iostream>
#include "Scene/StartScene.hpp"

Gen::StartScene::StartScene(std::shared_ptr<Renderer> _renderer)
{
	this->renderer = _renderer;
}

void Gen::StartScene::draw()
{
	renderer->clear();
	renderer->writeText(1, 1, "Welcome to MGeneration");
	renderer->refresh();
}
