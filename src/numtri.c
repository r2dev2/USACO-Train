/*
ID: ronak.b1
LANG: C
TASK: numtri
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


int R, count;
int nodes[1010][1010];
int cached[1010][1010];

int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}

void printarr( int arr[1010][1010] )
{
	for ( int i = 0; i < R; ++i )
	{
		for ( int j = 0; arr[i][j] != -1; ++j )
			printf( "%d ", arr[i][j] );
		printf( "\n" );
	}
}

int traverse_tree( int curr_index, int curr_row ) 
{
	int max = 0,
	    num_left = 0,
	    num_right = 0;
	if ( curr_row < R )
	{
		num_left = nodes[curr_row][curr_index] + traverse_tree_with_cache( curr_index, curr_row + 1 );
		num_right = nodes[curr_row][curr_index] + traverse_tree_with_cache( curr_index + 1, curr_row + 1 );
	}
	max = MAX(max, MAX(num_left, num_right));
	return max;
}

int traverse_tree_with_cache( int i, int j )
{
	if ( cached[i][j] == -1 )
	{
		int res = traverse_tree( i, j );
		cached[i][j] = res;
	}
	return cached[i][j];
}

int main()
{
	FILE *fin = fopen( "numtri.in", "r" );
	FILE *fout = fopen( "numtri.out", "w+" );

	fscanf( fin, "%d", &R );


	memset(nodes, -1, sizeof(nodes[0][0]) * 1010 * 1010);
	memset(cached, -1, sizeof(cached[0][0]) * 1010 * 1010);


	for ( int i = 0; i < R; ++i )
	{
		for ( int j = 0; j < i+1; ++j )
		{
			fscanf( fin, "%d", &nodes[i][j] );
		}
	}


	fprintf( fout, "%d\n", traverse_tree( 0, 0 )  );

	fclose( fin );
	fclose( fout );

	return 0;
}

