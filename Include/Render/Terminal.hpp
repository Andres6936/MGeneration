// Design by Joan Andrés.

#ifndef MGENERATION_TERMINAL_HPP
#define MGENERATION_TERMINAL_HPP

#include "Renderer.hpp"

namespace Gen
{

	class Terminal : public Renderer
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

	};

}

#endif //MGENERATION_TERMINAL_HPP
