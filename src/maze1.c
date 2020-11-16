/*
ID: ronak.b1
LANG: C++
TASK: maze1
*/

#include <assert.h>
#include <queue>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define i64 long long
#define i32 long
#define ui64 unsigned long long
#define ui32 unsigned long
#define ui16 unsigned int

#define MAX(a, b) ( a > b ? a : b )
#define MIN(a, b) ( a < b ? a : b )
#define VALID(x, y) ( 0 <= x && x < W && 0 <= y && y < H )

typedef struct Point {
	int x;
	int y;
} Point;

const char NORTH = 1;
const char EAST  = 2;
const char SOUTH = 4;
const char WEST  = 8;

FILE *fin, *fout;
int W, H; // 1 <= W <= 38, 1 <= H <= 100
char maze[38][100]; // maze[x][y]
int distances[38][100]; // distances[x][y] is the distance to exit at the point
Point exits[2]; // (exit[0].x, exit[0].y), (exit[1].x, exit[1].y);

int compare_int( const void *a, const void *b )
{
	return *((int*) a) - *((int*) b);
}

void advance( Point np, std::queue<Point> *q, int nd )
{
	if ( VALID( np.x, np.y ) && (distances[np.x][np.y] == 0 || nd < distances[np.x][np.y]) )
	{
		distances[np.x][np.y] = nd;
		q->push( np );
	}
}


int main()
{
	fin = fopen( "maze1.in", "r" );
	fout = fopen( "maze1.out", "w+" );

	fscanf( fin, "%d %d", &W, &H );

	int exit_count = 0;

	for ( int i = 0, w = 0, h = 0; i < 2 * H + 1; ++i, w = 0 )
	{
		h += !(!i) * !(i % 2);
		for ( int j = 0; j < 2 * W + 1; ++j )
		{
			w += !(!j) * !(j % 2);
			char c = '\n';
			while ( c == '\n' )
			{
				fscanf( fin, "%c", &c );
			}
			// printf( "(%d, %d, %c)", w, h, c );
			switch ( c )
			{
				case '-':
					if ( VALID( w, h - 1 ) )
					{
						maze[w][h - 1] |= SOUTH;
					}
					if ( VALID( w, h ) )
					{
						maze[w][h] |= NORTH;
					}
					break;
				case '|':
					if ( VALID( w - 1, h ) )
					{
						maze[w - 1][h] |= EAST;
					}
					if ( VALID( w, h ) )
					{
						maze[w][h] |= WEST;
					}
					break;
				case ' ':
					break;
			}
		}
		// printf( "\n" );
	}

	int is_exit = 0;
	for ( int w = 0; w < W; ++w )
	{
		for ( int h = 0; h < H; ++h )
		{
			// printf( "(%d)", maze[w][h] );
			if ( w == 0 )
			{
				is_exit = !(maze[w][h] & WEST);
			}
			else if ( w == W - 1 )
			{
				is_exit = !(maze[w][h] & EAST);
			}
			if ( h == 0 )
			{
				is_exit += !(maze[w][h] & NORTH);
			}
			else if ( h == H - 1 )
			{
				is_exit += !(maze[w][h] & SOUTH);
			}
			if ( is_exit )
			{
				is_exit = 0;
				exits[exit_count].x = w;
				exits[exit_count].y = h;
				exit_count++;
			}
		}
		// printf( "\n" );
	}

	printf( "\nExits at (%d, %d) and (%d, %d)\n", exits[0].x, exits[0].y, exits[1].x, exits[1].y );
	// assert (maze[4][0] == (EAST | NORTH));
	// assert (maze[0][0] == (WEST | NORTH | SOUTH));

	for ( int h = 0; h < exit_count; ++h )
	{
		distances[exits[0].x][exits[0].y] = 1;
	}

	for ( int h = 0; h < exit_count; ++h )
	{
		std::queue<Point> heads;
		heads.push( exits[h] );
		for ( int dist = 2; heads.size(); ++dist )
		{
			std::queue<Point> addto;
			while ( heads.size() )
			{
				Point p = heads.front();
				heads.pop();
				char sq = maze[p.x][p.y];
				if ( !(sq & NORTH) )
				{
					Point np = { .x = p.x, .y = p.y - 1 };
					advance( np, &addto, dist );
				}
				if ( !(sq & SOUTH) )
				{
					Point np = { .x = p.x, .y = p.y + 1 };
					advance( np, &addto, dist );
				}
				if ( !(sq & EAST) )
				{
					Point np = { .x = p.x + 1, p.y };
					advance( np, &addto, dist );
				}
				if ( !(sq & WEST) )
				{
					Point np = { .x = p.x - 1, p.y };
					advance( np, &addto, dist );
				}
			}
			heads = addto;
		}
	}

	int mex = INT_MIN;

	for ( int h = 0; h < H; ++h )
	{
		for ( int w = 0; w < W; ++w )
		{
			printf( "(%2d)", distances[w][h] );
			mex = MAX( mex, distances[w][h] );
		}
		printf( "\n" );
	}

	fprintf( fout, "%d\n", mex );

	fclose( fin );
	fclose( fout );

	return 0;
}

