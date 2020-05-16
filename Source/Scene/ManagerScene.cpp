// Design by Joan Andrés.

#include "Scene/ManagerScene.hpp"

Gen::ManagerScene::ManagerScene(std::shared_ptr<Renderer>& _renderer)
{
	menu = std::make_shared<MenuScene>(_renderer);
	play = std::make_shared<PlayScene>(_renderer);

	current = menu;
}

void Gen::ManagerScene::draw()
{
	current->draw();
}

void Gen::ManagerScene::clear()
{
	current->clear();
}

void Gen::ManagerScene::event()
{
	next(current->event());
}

void Gen::ManagerScene::update()
{
	current->update();
}

void Gen::ManagerScene::next(NextScene _scene)
{
	switch (_scene)
	{

	case NextScene::Menu:
		current = menu;
		break;

	case NextScene::Play:
		current = play;
		break;

	case NextScene::Stop:
		break;

	case NextScene::Exit:
		break;

	}
}
