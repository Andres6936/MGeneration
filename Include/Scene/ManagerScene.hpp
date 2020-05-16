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

		std::shared_ptr<PlayScene> play;
		std::shared_ptr<MenuScene> menu;

		std::shared_ptr<Scene> current;

	public:

		ManagerScene(std::shared_ptr<Renderer>& _renderer);

		void draw();

		void clear();

		void update();

	};

}

#endif //MGENERATION_MANAGERSCENE_HPP
