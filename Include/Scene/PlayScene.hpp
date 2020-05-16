// Design by Joan Andrés.

#ifndef MGENERATION_PLAYSCENE_HPP
#define MGENERATION_PLAYSCENE_HPP

#include <World.h>
#include "Scene.hpp"
#include "NextScene.hpp"

namespace Gen
{

	class PlayScene : public Scene
	{

	private:

		World world;
		Player player;

	public:

		PlayScene(std::shared_ptr<Renderer>& _renderer);

		void draw() override;

		void clear() override;

		NextScene event() override;

		void update() override;

	};

}

#endif //MGENERATION_PLAYSCENE_HPP
