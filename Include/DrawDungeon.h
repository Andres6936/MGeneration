// Only include file once
#pragma once

#include <BearLibTerminal/BearLibTerminal.hpp>
#include "World.h"
#include "Player.h"

namespace Gen
{
	void DrawDungeon(const World& world, Player& player);
}