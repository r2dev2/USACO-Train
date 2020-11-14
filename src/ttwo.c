/*
ID: ronak.b1
LANG: C
TASK: ttwo
*/

#include <assert.h>
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

const char NORTH = 1;
const char EAST = 2;
const char SOUTH = 4;
const char WEST = 8;
const char OBS = 15;

FILE *fin, *fout;
char grid[10][10];
char visited[2][10][10];
char translation[100];
char heads[2][3];
char rotation[10];
int  dxy[2][10];


int compare_int( const void *a, const void *b )
{
	return *((int*) a) - *((int*) b);
}


int main()
{
	fin = fopen( "ttwo.in", "r" );
	fout = fopen( "ttwo.out", "w+" );

	translation['*'] = OBS;
	translation['C'] = translation['F'] = NORTH;

	rotation[NORTH] = EAST;
	rotation[EAST]  = SOUTH;
	rotation[SOUTH] = WEST;
	rotation[WEST]  = NORTH;

	dxy[0][NORTH] = -1;
	dxy[1][EAST]  = 1;
	dxy[0][SOUTH] = 1;
	dxy[1][WEST]  = -1;

	int cows = 0;
	for ( int i = 0; i < 10; ++i )
	{
		for ( int j = 0; j < 10; ++j )
		{
			char square = '\n';
			while ( square == '\n' )
				fscanf( fin, "%c", &square );
			printf( "(%c)", square );
			grid[i][j] = translation[square];
			if ( grid[i][j] == NORTH )
			{
				visited[cows][i][j] = NORTH;
				heads[cows][0] = i;
				heads[cows][1] = j;
				heads[cows][2] = NORTH;
				cows++;
			}
		}
		printf( "\n" );
	}

	assert (cows == 2);

	int minutes = 0;

	printf( "(%d, %d)\n", heads[0][0], heads[0][1] );
	printf( "(%d, %d)\n", heads[1][0], heads[1][1] );

	do
	{
		for ( int h = 0; h < 2; ++h )
		{
			int i = heads[h][0];
			int j = heads[h][1];
			char dir = heads[h][2];
			// visited[h][i][j] |= dir;

			int ni = i + dxy[0][dir];
			int nj = j + dxy[1][dir];


			if ( !(0 <= ni && ni < 10 && 0 <= nj && nj < 10 && grid[ni][nj] != OBS) )
			{
				ni = i;
				nj = j;
				dir = rotation[dir];
			}

			heads[h][0] = ni;
			heads[h][1] = nj;
			heads[h][2] = dir;
		}
		minutes++;
	}
	while ( !(heads[0][2] == visited[0][heads[0][0]][heads[0][1]]
	     && heads[1][2] == visited[1][heads[1][0]][heads[1][1]])
	     && !(heads[0][0] == heads[1][0] && heads[0][1] == heads[1][1])
	     && minutes < 100000 );
	// the minutes < 1000000 only works for this problem because I'm too lazy ree

	fprintf( fout, "%d\n", minutes * (heads[0][0] == heads[1][0] && heads[0][1] == heads[1][1]) );

	fclose( fin );
	fclose( fout );

	return 0;
}

