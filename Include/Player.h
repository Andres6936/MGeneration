// Only include file once
#pragma once

#include <BearLibTerminal/BearLibTerminal.hpp>
#include <functional>

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

		std::reference_wrapper<World> world;

	public:

		Player(const std::reference_wrapper<World>& _world);

		// Methods

		void setPositionRandomAtMap();

		void moveTo(Direction direction);

		void handlerEventPlayer(int key);

		// Override

		void draw() override;

		// Getter

		int getX() const;

		int getY() const;
	};
}