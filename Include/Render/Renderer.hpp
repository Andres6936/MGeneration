// Design by Joan Andrés.

#ifndef MGENERATION_RENDERER_HPP
#define MGENERATION_RENDERER_HPP

namespace Gen
{
	class Renderer
	{

	public:

		virtual void clear() = 0;

		virtual void refresh() = 0;

		virtual int getKeyPressed() = 0;

	};
}

#endif //MGENERATION_RENDERER_HPP
