#include "Player.h"

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
	if (key == TK_UP)
	{
		moveTo(EDirection::NORTH, player);
	}
	else if (key == TK_DOWN)
	{
		moveTo(EDirection::SOUTH, player);
	}
	else if (key == TK_LEFT)
	{
		moveTo(EDirection::WEST, player);
	}
	else if (key == TK_RIGHT)
	{
		moveTo(EDirection::EAST, player);
	}
}
