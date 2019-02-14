#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ncurses.h>

#include "Source/Include/BearLibTerminal.h"
#include "Source/Include/World.h"
#include "Source/Include/Player.h"
#include "Source/Include/Vector.h"
#include "Source/Include/EDirection.h"
#include "Source/Include/DrawDungeon.h"

const unsigned int walks = 1000;
const unsigned int steps = 2500;

static void usage( void )
{
    puts( "Usage:" );
    puts( "\tascii-owrpg [file]" );
    puts( "\tascii-owrpg -h" );
}

World loadWorld( const char *filename )
{
    FILE *stream = fopen( filename, "r" );

    if ( stream == NULL )
    {
        puts( "Error while reading (open) file" );
        exit( EXIT_FAILURE );
    }

    World newWorld;

    // NOTE: Deleteme
    newWorld.width = 1000;
    newWorld.height = 1000;

    int character;
    int row = 0;
    int column = 0;

    while (( character = fgetc( stream )) != EOF)
    {
        if ( character == '\n' )
        {
            row++;
            column = 0;
        }
        else
        {
            newWorld.map[row][column] = (char) character;
            column++;
        }
    }

    fclose( stream );

    return newWorld;
}

World newWorld( int height, int width, int walks, int steps, Player* player )
{
    // Generate an seed for new map.
    //srand( time(NULL));

    World newWorld;

    newWorld.height = MAP_HEIGHT;
    newWorld.width = MAP_WIDTH;

    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            newWorld.map[x][y] = '#';
        }
    }

    Vector2D *freeCells = malloc( sizeof( Vector2D ) * walks * steps ); // too much, but I don't care...

    int counter = 0;

    for ( int i = 0; i < walks; ++i )
    {
        int y, x;
        y = rand( ) % height;
        x = rand( ) % width;
        for ( int j = 0; j < steps; ++j )
        {
            EDirection direction = rand( ) % 4;
            switch ( direction )
            {
                case NORTH:
                    if (( y - 1 ) > 1 )
                    {
                        newWorld.map[ --y ][ x ] = '.';
                        freeCells[ counter ].y = y;
                        freeCells[ counter ].x = x;
                        counter++;
                    }
                    break;
                case EAST:
                    if (( x + 1 ) < width - 1 )
                    {
                        newWorld.map[ y ][ ++x ] = '.';
                        freeCells[ counter ].y = y;
                        freeCells[ counter ].x = x;
                        counter++;
                    }
                    break;
                case WEST:
                    if (( x - 1 ) > 1 )
                    {
                        newWorld.map[ y ][ --x ] = '.';
                        freeCells[ counter ].y = y;
                        freeCells[ counter ].x = x;
                        counter++;
                    }
                    break;
                case SOUTH:
                    if (( y + 1 ) < height - 1 )
                    {
                        newWorld.map[ ++y ][ x ] = '.';
                        freeCells[ counter ].y = y;
                        freeCells[ counter ].x = x;
                        counter++;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    Vector2D coodinatePlayerRandom = freeCells[ rand( ) % counter ];

    player->x = coodinatePlayerRandom.x;
    player->y = coodinatePlayerRandom.y;

    free( freeCells );
    return newWorld;
}

int main( int argc, char *argv[] )
{
    World world;
    Player player;

    // We assume that the second parameter points to a file that contains
    // a map already generated.
    if ( argc == 2 )
    {
        world = loadWorld( argv[ 1 ] );
        player.x = 60;
        player.y = 30;
    }
    else
    {
        // If there are not argument, generate a new map.
        world = newWorld( MAP_HEIGHT, MAP_WIDTH, walks, steps, &player );
    }

    terminal_open();
    terminal_set("terminal: encoding=437");
    terminal_set("window: size=80x25, cellsize=auto, title=MGeneration");

    // Key pressed for user
    int key;

    _Bool running = true;

    terminal_clear();
    DrawDungeon(&world, &player);
    terminal_refresh();

    // Main Loop
    while ( running )
    {
        key = terminal_read( );

        // The user close the window or app
        if (key == TK_CLOSE)
        {
            running = false;
        }

        // Handle events
        handlerEventPlayer(key, &player);

        // Clear, Draw and Refresh
        terminal_clear();
        DrawDungeon(&world, &player);
        terminal_refresh();
    }

    terminal_close();

    return 0;
}
