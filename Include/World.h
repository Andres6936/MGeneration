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

	using VectorChar = std::vector<char>;

	class World final : public VectorChar
	{

	private:

		int height; // The height of the world map
		int width;  // The width of the world map

	public:

		// Construct

		World() noexcept;

		World(int width, int height) noexcept;

		World(int width, int height, int walks, int steps) noexcept;

		World(const char* filename) noexcept;

		// Methods

		void draw(std::unique_ptr<Renderer>& renderer, const Player& player);

		// Getters

		int getWidth() const;

		int getHeight() const;

		char getGlyph(int x, int y) const;

		// Setters

		void setGlyph(int x, int y, char glyph);

	};
}