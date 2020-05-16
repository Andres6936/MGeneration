#include "DrawDungeon.h"

void DrawDungeon(const World& world, Player& player)
{

	// WINDOW_WIDTH = 80;
	// WINDOW_HEIGHT = 25;

	int startX = player.getX() - (80 / 2);
	int startY = player.getY() - (25 / 2);

	if (player.getX() < 80 / 2)
	{
		startX = 0;
	}
	else if (player.getX() >= MAP_WIDTH - (80 / 2))
	{
		startX = MAP_WIDTH - 80;
	}

	if (player.getY() < 25 / 2)
	{
		startY = 0;
	}
	else if (player.getY() >= MAP_HEIGHT - (25 / 2))
	{
		startY = MAP_HEIGHT - 25;
	}

	for (int x = 0; x < 80; x++)
	{
		for (int y = 0; y < 25; y++)
		{
			TerminalColor(ColorFromName("white"));
			TerminalPut(x, y, world.getGlyph(x + startX, y + startY));
		}
	}

	TerminalColor(ColorFromName("orange"));
	TerminalPut(player.getX() - startX, player.getY() - startY, '@');
}
