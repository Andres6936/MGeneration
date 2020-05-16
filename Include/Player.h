// Only include file once
#pragma once

#include <BearLibTerminal/BearLibTerminal.hpp>

#include "Direction.h"
#include "Entity.hpp"

namespace Gen
{

	class World;

	class Player : public Entity
	{

	private:

		int x;
		int y;

	public:

		Player();

		Player(int coordinateX, int coordinateY);

		// Methods

		void setPositionRandomAtMap(World& world);

		void moveTo(Direction direction);

		void handlerEventPlayer(int key);

		// Override

		void draw() override;

		// Getter

		int getX() const;

		int getY() const;
	};
}