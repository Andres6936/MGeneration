// Only include file once
#pragma once

#include <vector>
#include <memory>

#include "Cell.hpp"
#include "Player.h"
#include "Render/Renderer.hpp"

namespace Gen
{

	const unsigned short MAP_HEIGHT = 1000;
	const unsigned short MAP_WIDTH = 1000;

	using VectorCell = std::vector<Cell>;

	class World final : public VectorCell
	{

	private:

		int height; // The height of the world map
		int width;  // The width of the world map

	public:

		// Construct

		World() noexcept;

		World(int width, int height) noexcept;

		World(const char* filename) noexcept;

		// Methods

		void draw(std::shared_ptr<Renderer>& renderer, const Player& player);

		void generateByAutomateCellular(int walks, int steps);

		// Getters

		int getWidth() const;

		int getHeight() const;

		int getGlyph(int x, int y) const;

		// Setters

		void setGlyph(int x, int y, int glyph);

	};
}