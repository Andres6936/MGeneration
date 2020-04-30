// Only include file once
#pragma once

#include <BearLibTerminal/BearLibTerminal.hpp>
#include "EDirection.h"

class World;

class Player
{

public:

	int x;
	int y;

public:

	Player();

	Player(int coordinateX, int coordinateY);

	void setPositionRandomAtMap(World& world);

};

void moveTo(EDirection direction, Player* player);

void handlerEventPlayer(int key, Player* player);
