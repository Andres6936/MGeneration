// Only include file once
#pragma once

#include "BearLibTerminal.h"
#include "EDirection.h"

typedef struct
{

    int x;
    int y;

} Player;

void moveTo( EDirection direction, Player *player );

void handlerEventPlayer(int key, Player *player);
