// Design by Joan Andrés.

#include <BearLibTerminal/BearLibTerminal.hpp>
#include "Scene/MenuScene.hpp"

using namespace Gen;

MenuScene::MenuScene(std::shared_ptr<Renderer>& _renderer)
{
	this->renderer = _renderer;
}

void MenuScene::draw()
{
	renderer->writeText(1, 1, "Welcome to MGeneration");
	renderer->writeText(1, 2, "Select a option");
	renderer->writeText(1, 4, "a) Generate map");
	renderer->writeText(1, 5, "b) Exit of app");
	renderer->refresh();
}

void MenuScene::clear()
{

}

void MenuScene::update()
{

}

NextScene MenuScene::event()
{
	while (true)
	{
		if (renderer->getKeyPressed() == TK_A) return NextScene::Play;
		if (renderer->getKeyPressed() == TK_B) return NextScene::Exit;
	}
}
