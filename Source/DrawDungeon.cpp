#include "DrawDungeon.h"

void DrawDungeon(World* world, Player* player)
{

	// WINDOW_WIDTH = 80;
	// WINDOW_HEIGHT = 25;

	int startX = player->x - (80 / 2);
	int startY = player->y - (25 / 2);

	if (player->x < 80 / 2)
	{
		startX = 0;
	}
	else if (player->x >= MAP_WIDTH - (80 / 2))
	{
		startX = MAP_WIDTH - 80;
	}

	if (player->y < 25 / 2)
	{
		startY = 0;
	}
	else if (player->y >= MAP_HEIGHT - (25 / 2))
	{
		startY = MAP_HEIGHT - 25;
	}

	for (int x = 0; x < 80; x++)
	{
		for (int y = 0; y < 25; y++)
		{
			TerminalPut(x, y, world->getGlyph(x + startX, y + startY));
		}
	}

	TerminalPut(player->x - startX, player->y - startY, '@');
}
