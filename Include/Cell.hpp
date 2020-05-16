// Design by Joan Andrés.

#ifndef MGENERATION_CELL_HPP
#define MGENERATION_CELL_HPP

#include <memory>

#include "Item.hpp"
#include "Props.hpp"
#include "Entity.hpp"

namespace Gen
{
	class Cell final
	{

	private:

		int code = 0;

		Item item;
		Props props;
		std::unique_ptr<Entity> entity;

	public:

		// Constructs

		Cell() noexcept = default;

		Cell(int _code) noexcept: code(_code)
		{
		};

		// Getters

		int getCode() const;

	};
}

#endif //MGENERATION_CELL_HPP
