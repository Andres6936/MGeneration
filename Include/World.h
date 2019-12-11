// Only include file once
#pragma once

typedef struct
{
	int height; /* The height of the world map */
	int width;  /* The width of the world map */
	int y_pos;  /* Player y position */
	int x_pos;  /* Player x position */
	char map[1000][1000];

} World;

extern const unsigned short MAP_HEIGHT;

extern const unsigned short MAP_WIDTH;
