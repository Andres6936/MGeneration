// Relax, You can deleted this sentence
#pragma clang diagnostic push
// Relax, You can deleted this sentence
#pragma ide diagnostic ignored "cert-msc30-c"

#include "Player.h"
#include "World.h"

using namespace Gen;

Player::Player(const std::reference_wrapper<World>& _world) : world(_world)
{
	this->x = 0;
	this->y = 0;

	setPositionRandomAtMap();
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

void Player::setPositionRandomAtMap()
{
	x = std::rand() % world.get().getWidth();
	y = std::rand() % world.get().getHeight();
}

int Player::getX() const
{
	return x;
}

int Player::getY() const
{
	return y;
}

void Player::draw()
{

}
