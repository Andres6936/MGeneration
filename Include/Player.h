// Only include file once
#pragma once

#include <BearLibTerminal/BearLibTerminal.hpp>
#include "Direction.h"

class World;

class Player
{

private:

	int x;
	int y;

public:

	Player();

	Player(int coordinateX, int coordinateY);

	void setPositionRandomAtMap(World& world);

	void moveTo(Direction direction);

	void handlerEventPlayer(int key);

	// Getter

	int getX() const;

	int getY() const;
};