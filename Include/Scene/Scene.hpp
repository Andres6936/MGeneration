// Design by Joan Andrés.

#ifndef MGENERATION_SCENE_HPP
#define MGENERATION_SCENE_HPP

#include <memory>

#include "Render/Renderer.hpp"
#include "NextScene.hpp"

namespace Gen
{

	class Scene
	{

	protected:

		std::shared_ptr<Renderer> renderer;

	public:

		// Destructor

		virtual ~Scene() = default;

		// Methods

		virtual void draw() = 0;

		virtual void clear() = 0;

		virtual NextScene event() = 0;

		virtual void update() = 0;

	};

}

#endif //MGENERATION_SCENE_HPP
