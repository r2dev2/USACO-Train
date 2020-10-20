/*
ID: ronak.b1
LANG: C
TASK: wormhole
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


typedef struct Wormhole Wormhole;

struct Wormhole{
	int x;
	int y;
	Wormhole *right;
	Wormhole *portal;
};


int N;
Wormhole holes[15];
char takenset[33000];

void printarr( int *arr )
{
	printf( "[" );
	for ( int *a = arr; a < arr + 14; ++a )
		printf( "%d, ", *a );
	printf( "%d]\n", arr[14] );
}

int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}

int hash_arr( int *arr )
{
	int sum = 0;
	int multiple = 1;
	for ( int power = 0; power < 15; ++power, multiple *= 2 )
		sum += arr[power] * multiple;
	return sum;
}

int is_valid( int startnum, Wormhole w, char go_right, int depth )
{
	if ( depth > N )
		return 0;
	if ( holes[startnum].x == w.x && holes[startnum].y == w.y && depth )
		return 1;
	if ( 1 || go_right )
	{
		printf( "(%d, %d)\n", w.x, w.y );
		if ( w.right != NULL )
			return is_valid( startnum, *(w.right->portal), 0, depth + 2 );
		else
			return 0;
	}
	else
	{
		assert (w.portal != NULL);
		return is_valid( startnum, *w.portal, 1, depth + 2 );
	}
}

int get_num_helper( int *has_been_done, int done_left )
{
	int count = 0;
	if ( done_left == 0 )
	{
		for ( int i = 0; i < N; ++i )
			count += is_valid( i, holes[i], 1, 0 ) + is_valid( i, holes[i], 0, 0 );
		return count;
	}
	for ( int i = 0; i < N; ++i )
	{
		for ( int j = 0; j < N; ++j )
		{
			if ( i != j && !has_been_done[i] && !has_been_done[j] )
			{
				int dones[15];
				memcpy( dones, has_been_done, 15*sizeof(int) );
				holes[i].portal = holes + j;
				holes[j].portal = holes + i;
				dones[i] = 1;
				dones[j] = 1;
				count += get_num_helper( dones, done_left - 2 );
				holes[i].portal = holes[j].portal = NULL;
			}
		}
	}
	return count;
}

int get_num()
{
	int dones[15] = {0};
	return get_num_helper( dones, N );
}

int main()
{
	FILE *fin = fopen( "wormhole.in", "r" );
	FILE *fout = fopen( "wormhole.out", "w+" );
	

	fscanf( fin, "%d", &N );
	for ( int i = 0; i < N; ++i )
		fscanf( fin, "%d %d", &holes[i].x, &holes[i].y );


	for ( int i = 0; i < N; ++i )
	{
		Wormhole hole = holes[i];
		int mindistance = INT_MAX;
		for ( int j = 0; j < N; ++j )
		{
			if ( i != j )
			{
				int xdist = holes[j].x - holes[i].x;
				if ( holes[i].y == holes[j].y && xdist < mindistance && holes[j].x > holes[i].x )
				{
					holes[i].right = &holes[j];
					mindistance = xdist;
				}
			}
		}
	}

	

	int count = 0;
	count += get_num();

	fprintf( fout, "%d\n", count );

	fclose( fin );
	fclose( fout );

	return 0;
}

