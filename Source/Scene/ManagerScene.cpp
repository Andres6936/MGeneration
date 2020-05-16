// Design by Joan Andrés.

#include "Scene/ManagerScene.hpp"

using namespace Gen;

ManagerScene::ManagerScene(std::shared_ptr<Renderer>& _renderer)
{
	menu = std::make_shared<MenuScene>(_renderer);
	play = std::make_shared<PlayScene>(_renderer);

	current = menu;
}

void ManagerScene::draw()
{
	current->draw();
}

void ManagerScene::clear()
{
	current->clear();
}

void ManagerScene::event()
{
	next(current->event());
}

void ManagerScene::update()
{
	current->update();
}

void ManagerScene::next(NextScene _scene)
{
	// The scene is the same and not is necessary
	// change of scene or show a new.
	if (_scene == currentShow) return;

	switch (_scene)
	{

	case NextScene::None:
		// Continue with the execution.
		return;

	case NextScene::Menu:
		currentShow = _scene;
		current = menu;
		break;

	case NextScene::Play:
		currentShow = _scene;
		current = play;
		break;

	case NextScene::Stop:
		break;

	case NextScene::Exit:
		running = false;
		break;

	}
}

bool ManagerScene::isRunning() const
{
	return running;
}