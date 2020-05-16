// Design by Joan Andrés.

#include "Scene/ManagerScene.hpp"

Gen::ManagerScene::ManagerScene(std::shared_ptr<Renderer>& _renderer)
{
	menu = std::make_unique<MenuScene>(_renderer);
	play = std::make_unique<PlayScene>(_renderer);
}

void Gen::ManagerScene::draw()
{
	menu->draw();
}
