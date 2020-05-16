// Relax, You can deleted this sentence
#pragma clang diagnostic push
// Relax, You can deleted this sentence
#pragma ide diagnostic ignored "cert-msc30-c"

#include "Player.h"
#include "World.h"

void moveTo(EDirection direction, Player* player)
{

	if (direction == EDirection::NORTH)
	{
		player->y--;
	}
	else if (direction == EDirection::SOUTH)
	{
		player->y++;
	}
	else if (direction == EDirection::WEST)
	{
		player->x--;
	}
	else if (direction == EDirection::EAST)
	{
		player->x++;
	}
}

void handlerEventPlayer(int key, Player* player)
{
	if (key == TK_UP or key == TK_KP_8)
	{
		moveTo(EDirection::NORTH, player);
	}
	else if (key == TK_DOWN or key == TK_KP_2)
	{
		moveTo(EDirection::SOUTH, player);
	}
	else if (key == TK_LEFT or key == TK_KP_4)
	{
		moveTo(EDirection::WEST, player);
	}
	else if (key == TK_RIGHT or key == TK_KP_6)
	{
		moveTo(EDirection::EAST, player);
	}
}

Player::Player()
{
	x = 0;
	y = 0;
}

Player::Player(int coordinateX, int coordinateY)
{
	x = coordinateX;
	y = coordinateY;
}

void Player::setPositionRandomAtMap(World& world)
{
	x = std::rand() % world.getWidth();
	y = std::rand() % world.getHeight();
}
