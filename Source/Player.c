#include "Include/Player.h"

void moveTo( EDirection direction, Player *player )
{

    if (direction == NORTH)
    {
        player->y--;
    }
    else if (direction == SOUTH)
    {
        player->y++;
    }
    else if (direction == WEST)
    {
        player->x--;
    }
    else if (direction == EAST)
    {
        player->x++;
    }
}

void handlerEventPlayer(int key, Player* player)
{
    if (key == TK_UP)
    {
        moveTo( NORTH, player );
    }
    else if (key == TK_DOWN)
    {
        moveTo( SOUTH, player );
    }
    else if (key == TK_LEFT)
    {
        moveTo( WEST, player );
    }
    else if (key == TK_RIGHT)
    {
        moveTo( EAST, player );
    }
}
