// Design by Joan Andrés.

#ifndef MGENERATION_TERMINAL_HPP
#define MGENERATION_TERMINAL_HPP

#include "Renderer.hpp"

namespace Gen
{

	class Terminal final : public Renderer
	{

	public:

		// Construct

		Terminal();

		// Destructor

		~Terminal();

		// Override

		void clear() override;

		void refresh() override;

		int getKeyPressed() override;

		void write(UInt32 x, UInt32 y, int code) override;

		void setBackgroundColor(const char* name) override;

		void writeText(UInt32 x, UInt32 y, std::string text) override;

	};

}

#endif //MGENERATION_TERMINAL_HPP
