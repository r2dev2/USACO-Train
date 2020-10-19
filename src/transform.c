/*
ID: ronak.b1
LANG: C
TASK: transform
*/

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define i64 long long
#define uint unsigned int

#define MAX(a, b) ( a > b ? a : b )
#define MIN(a, b) ( a < b ? a : b )

int N;
float center;
char squares[3][11][11];
char str[15];

int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}


int squares_are_equal()
{
	for ( int i = 0; i < N; ++i )
		for ( int j = 0; j < N; ++j )
			if ( squares[0][i][j] != squares[1][i][j] )
				return 0;
	return 1;
}


void reflect()
{
	char new_squares[11][11];
	for ( int y = 0; y < N; ++y )
		for ( int x = 0; x < N; ++x )
			new_squares[y][N-x-1] = squares[0][y][x];

	for ( int i = 0; i < N; ++i )
		for ( int j = 0; j < N; ++j )
			squares[0][i][j] = new_squares[i][j];
}


void rotate_90_degrees_counterclockwise()
{
    // Consider all squares one by one 
    for (int x = 0; x < N / 2; x++) { 
        // Consider elements in group 
        // of 4 in current square 
        for (int y = x; y < N - x - 1; y++) { 
            // Store current cell in 
            // temp variable 
            char temp = squares[0][x][y]; 
  
            // Move values from right to top 
            squares[0][x][y] = squares[0][y][N - 1 - x]; 
  
            // Move values from bottom to right 
            squares[0][y][N - 1 - x] 
                = squares[0][N - 1 - x][N - 1 - y]; 
  
            // Move values from left to bottom 
            squares[0][N - 1 - x][N - 1 - y] 
                = squares[0][N - 1 - y][x]; 
  
            // Assign temp to left 
            squares[0][N - 1 - y][x] = temp; 
        } 
    } 
}

void rotate_90_degrees()
{
	for ( int i = 0; i < 3; ++i )
		rotate_90_degrees_counterclockwise();
}


int main()
{
	FILE *fin = fopen( "transform.in", "r" );
	FILE *fout = fopen( "transform.out", "w+" );


	fscanf( fin, "%d", &N );

	for ( int i = 0; i < 2; ++i )
		for ( int j = 0; j < N; ++j )
		{
			fscanf( fin, "%s", str );
			for ( int k = 0; k < N; ++k )
			{
				squares[i][j][k] = str[k];
				if ( i == 0 )
					squares[2][j][k] = str[k];
			}
		}

	if ( N % 2 )
		center = N / 2 + 1;
	else
		center = N / 2 + .5;

	for ( int i = 0; i < N; ++i )
	{
		for ( int j = 0; j < N; ++j )
			printf( "%c ", squares[0][i][j] );
		printf( "\n" );
	}
	printf( "\n" );

	int exitcode = 0;

	if ( squares_are_equal() )
		exitcode = 6;
	
	if ( !exitcode || exitcode == 6 )
	{
		rotate_90_degrees();

		if ( squares_are_equal() )
			exitcode = 1;
	}

	if ( !exitcode || exitcode == 6 )
	{
		rotate_90_degrees();

		if ( squares_are_equal() )
			exitcode = 2;
	}

	if ( !exitcode || exitcode == 6 )
	{
		rotate_90_degrees();

		if ( squares_are_equal() )
			exitcode = 3;
	}
	
	if ( !exitcode || exitcode == 6 )
	{
		rotate_90_degrees();
		reflect();

		if ( squares_are_equal() )
			exitcode = 4;
	}

	if ( !exitcode || exitcode == 6 )
		for ( int i = 0; i < 3; ++i )
		{
			rotate_90_degrees();
			if ( squares_are_equal() )
				exitcode = 5;
		}

	if ( !exitcode )
		exitcode = 7;

	for ( int i = 0; i < N; ++i )
	{
		for ( int j = 0; j < N; ++j )
			printf( "%c ", squares[0][i][j] );
		printf( "\n" );
	}


	fprintf( fout, "%d\n", exitcode );


	fclose( fin );
	fclose( fout );

	return 0;
}

