// Relax, You can deleted this sentence
#pragma clang diagnostic push
// Relax, You can deleted this sentence
#pragma ide diagnostic ignored "cert-msc30-c"

#include "Player.h"
#include "World.h"

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

void Player::moveTo(Direction direction)
{

	if (direction == Direction::North)
	{
		y--;
	}
	else if (direction == Direction::South)
	{
		y++;
	}
	else if (direction == Direction::West)
	{
		x--;
	}
	else if (direction == Direction::East)
	{
		x++;
	}
}

void Player::handlerEventPlayer(int key)
{
	if (key == TK_UP or key == TK_KP_8)
	{
		moveTo(Direction::North);
	}
	else if (key == TK_DOWN or key == TK_KP_2)
	{
		moveTo(Direction::South);
	}
	else if (key == TK_LEFT or key == TK_KP_4)
	{
		moveTo(Direction::West);
	}
	else if (key == TK_RIGHT or key == TK_KP_6)
	{
		moveTo(Direction::East);
	}
}

void Player::setPositionRandomAtMap(World& world)
{
	x = std::rand() % world.getWidth();
	y = std::rand() % world.getHeight();
}

int Player::getX() const
{
	return x;
}

int Player::getY() const
{
	return y;
}
