// Design by Joan Andrés.

#ifndef MGENERATION_MANAGERSCENE_HPP
#define MGENERATION_MANAGERSCENE_HPP

#include <memory>

#include "MenuScene.hpp"
#include "PlayScene.hpp"

namespace Gen
{

	class ManagerScene
	{

	private:

		bool running = true;

		NextScene currentShow = NextScene::Menu;

		std::shared_ptr<PlayScene> play;
		std::shared_ptr<MenuScene> menu;

		std::shared_ptr<Scene> current;

	public:

		ManagerScene(std::shared_ptr<Renderer>& _renderer);

		void draw();

		void clear();

		void event();

		void update();

		void next(NextScene _scene);

		bool isRunning() const;

	};

}

#endif //MGENERATION_MANAGERSCENE_HPP
