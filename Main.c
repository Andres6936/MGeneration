#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ncurses.h>

#include "Source/Include/BearLibTerminal.h"
#include "Source/Include/World.h"
#include "Source/Include/Player.h"
#include "Source/Include/DrawDungeon.h"

const int BUFFER_MINIMUN_SIZE = 10;
const unsigned int walks = 1000;
const unsigned int steps = 2500;

static void usage( void )
{
    puts( "Usage:" );
    puts( "\tascii-owrpg [file]" );
    puts( "\tascii-owrpg -h" );
}

typedef struct
{
    int y;
    int x;

} Coordinate2D;

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT

} EDirection;

World loadWorld( const char *filename )
{
    FILE *stream = fopen( filename, "r" );

    if ( !stream )
    {
        perror( "Error while reading file" );
        exit( EXIT_FAILURE );
    }

    char *buf = malloc( sizeof( char ) * BUFFER_MINIMUN_SIZE );

    int bufferSize = BUFFER_MINIMUN_SIZE;

    int firstLineLength = 0;
    int currentLineLength = 0;

    _Bool firstLine = true;
    int line_number = 0;

    World new_world;

    _Bool playerAlreadyFound = false;

    int c;

    while (( c = getc( stream )) != EOF)
    {
        if ( c == '\n' )
        {
            if ( firstLine )
            {
                firstLineLength = currentLineLength;
                new_world.width = firstLineLength;
                firstLine = false;
            }
            else
            {
                if ( currentLineLength != firstLineLength )
                {
                    fprintf( stderr, "Error: map is not square\n" );
                    exit( EXIT_FAILURE );
                }
            }
//            new_world.map = realloc( ew_world.map, sizeof( char * ) * ( line_number + 1 ));
//            new_world.map[ line_number ] = malloc( sizeof( char ) * currentLineLength );
            memcpy( new_world.map[ line_number ], buf, currentLineLength + 1 );
            line_number++;
            currentLineLength = 0;
            free( buf );
            buf = malloc( sizeof( char ) * BUFFER_MINIMUN_SIZE );
            bufferSize = BUFFER_MINIMUN_SIZE;
            continue;
        }
        else if (( c != '#' ) && ( c != '.' ) && ( c != '@' ))
        {
            fprintf( stderr,
                     "Unknown character \"%c\" in the data file \"%s\"\n at line %zu, column %zu\n",
                     c, filename, line_number + 1, currentLineLength + 1 );
            exit( EXIT_FAILURE );
        }
        else if ( c == '@' )
        {
            if ( playerAlreadyFound )
            {
                fprintf( stderr, "More than one player position found\n" );
                exit( EXIT_FAILURE );
            }
            new_world.x_pos = currentLineLength;
            new_world.y_pos = line_number;
            c = '.';
            playerAlreadyFound = true;
        }
        else if ( bufferSize <= currentLineLength )
        {
            buf = realloc( buf, ( bufferSize + BUFFER_MINIMUN_SIZE ) * sizeof( char ));
            bufferSize += BUFFER_MINIMUN_SIZE;
        }
        buf[ currentLineLength++ ] = c;
    }

    free( buf );

    if ( !playerAlreadyFound )
    {
        fprintf( stderr, "No player was found on the map\n" );
        exit( EXIT_FAILURE );
    }

    new_world.height = line_number;

    if ( !feof( stream ))
    {
        perror( "Error while reading file" );
        exit( EXIT_FAILURE );
    }

    fclose( stream );

#if DEBUG
    puts("The map has been loaded sucessfully.");
#endif

    return new_world;
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

    Coordinate2D *freeCells = malloc( sizeof( Coordinate2D ) * walks * steps ); // too much, but I don't care...

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
                case UP:
                    if (( y - 1 ) > 1 )
                    {
                        newWorld.map[ --y ][ x ] = '.';
                        freeCells[ counter ].y = y;
                        freeCells[ counter ].x = x;
                        counter++;
                    }
                    break;
                case RIGHT:
                    if (( x + 1 ) < width - 1 )
                    {
                        newWorld.map[ y ][ ++x ] = '.';
                        freeCells[ counter ].y = y;
                        freeCells[ counter ].x = x;
                        counter++;
                    }
                    break;
                case LEFT:
                    if (( x - 1 ) > 1 )
                    {
                        newWorld.map[ y ][ --x ] = '.';
                        freeCells[ counter ].y = y;
                        freeCells[ counter ].x = x;
                        counter++;
                    }
                    break;
                case DOWN:
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

    Coordinate2D coodinatePlayerRandom = freeCells[ rand( ) % counter ];

    player->x = coodinatePlayerRandom.x;
    player->y = coodinatePlayerRandom.y;

    free( freeCells );
    return newWorld;
}

void moveTo( EDirection direction, Player *player )
{

    if (direction == UP)
    {
        player->y--;
    }
    else if (direction == DOWN)
    {
        player->y++;
    }
    else if (direction == LEFT)
    {
        player->x--;
    }
    else if (direction == RIGHT)
    {
        player->x++;
    }
}

int main( int argc, char *argv[] )
{
    if ( argc > 2 )
    {
        usage( );
        exit( EXIT_FAILURE );
    }
    if (( argc == 2 ) && ( !strcmp( argv[ 1 ], "-h" ) || !strcmp( argv[ 1 ], "--help" )))
    {
        usage( );
        exit( EXIT_SUCCESS );
    }

    World world;
    Player player;

    if ( argc == 2 )
    {
        world = loadWorld( argv[ 1 ] );
    }
    else
    {
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

    while ( running )
    {
        key = terminal_read( );

        if (key == TK_UP)
        {
            moveTo( UP, &player );
        }
        else if (key == TK_DOWN)
        {
            moveTo( DOWN, &player );
        }
        else if (key == TK_LEFT)
        {
            moveTo( LEFT, &player );
        }
        else if (key == TK_RIGHT)
        {
            moveTo( RIGHT, &player );
        }
        else if (key == TK_CLOSE)
        {
            running = false;
        }

        // Clear, Draw and Refresh
        terminal_clear();
        DrawDungeon(&world, &player);
        terminal_refresh();
    }

    terminal_close();

    return 0;
}
