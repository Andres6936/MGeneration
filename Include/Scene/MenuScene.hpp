// Design by Joan Andrés.

#ifndef MGENERATION_MENUSCENE_HPP
#define MGENERATION_MENUSCENE_HPP

#include "Scene.hpp"
#include "NextScene.hpp"

namespace Gen
{

	class MenuScene : public Scene
	{

	public:

		MenuScene(std::shared_ptr<Renderer>& _renderer);

		void draw() override;

		void clear() override;

		NextScene event() override;

		void update() override;

	};

}

#endif //MGENERATION_MENUSCENE_HPP
