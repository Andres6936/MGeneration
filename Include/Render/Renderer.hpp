// Design by Joan Andrés.

#ifndef MGENERATION_RENDERER_HPP
#define MGENERATION_RENDERER_HPP

#include <cstdint>

namespace Gen
{
	class Renderer
	{

	protected:

		using UInt32 = std::uint32_t;

	public:

		virtual void clear() = 0;

		virtual void refresh() = 0;

		virtual int getKeyPressed() = 0;

		virtual void write(UInt32 x, UInt32 y, int code) = 0;

		virtual void setBackgroundColor(const char* name) = 0;

	};
}

#endif //MGENERATION_RENDERER_HPP
