// Design by Joan Andrés.

#ifndef MGENERATION_STARTSCENE_HPP
#define MGENERATION_STARTSCENE_HPP

#include "Scene.hpp"

namespace Gen
{

	class StartScene : public Scene
	{

	public:

		StartScene(std::shared_ptr<Renderer> _renderer);

		void draw() override;

	};

}

#endif //MGENERATION_STARTSCENE_HPP
