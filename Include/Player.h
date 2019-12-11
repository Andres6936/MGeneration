// Only include file once
#pragma once

#include "BearLibTerminal.hpp"
#include "EDirection.h"

class Player
{

public:

	int x;
	int y;

public:

	Player();

	Player(int coordinateX, int coordinateY);

	void setCoordinateX(int X);

	void setCoordinateY(int Y);

};

void moveTo(EDirection direction, Player* player);

void handlerEventPlayer(int key, Player* player);
