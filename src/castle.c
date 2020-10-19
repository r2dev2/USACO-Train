/*
ID: ronak.b1
LANG: C
TASK: castle
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

#define NORTH ((char) 2)
#define SOUTH ((char) 8)
#define EAST ((char) 4)
#define WEST ((char) 1)


FILE *fin, *fout;

typedef struct {
	char a[50][50];
} VV;

typedef struct {
	VV visited;
	char has_modified_room;
	struct {
		int m;
		int n;
	} head;
	struct {
		int m;
		int n;
	} modified;
	int m;
	int n;
} Castle;


typedef struct {
	VV visited;
	int res;
} CastleResult;

Castle castle;
VV rooms;
char start_room_set[50][50];
int count;

int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}


CastleResult get_number_modules_in_room( Castle cas, int depth, VV *rooms )
{
	CastleResult res;
	res.visited = cas.visited;
	int max = 0;
	int break_max = 0;
	char has_been_visited = cas.visited.a[cas.head.m][cas.head.n];
	char cr = rooms->a[cas.head.m][cas.head.n];
	char can_go_north = cas.head.n > 0 && !cas.visited.a[cas.head.m][cas.head.n-1];
	char can_go_south = cas.head.n < cas.n - 1 && !cas.visited.a[cas.head.m][cas.head.n+1];
	char can_go_west = cas.head.m > 0 && !cas.visited.a[cas.head.m-1][cas.head.n];
	char can_go_east = cas.head.m < cas.m - 1 && !cas.visited.a[cas.head.m+1][cas.head.n];

	count++;
	
	if ( !has_been_visited ) // && depth < castle.m*castle.n + 10 )
	{
		max = break_max = 1;
		cas.visited.a[cas.head.m][cas.head.n] = 1;
		start_room_set[cas.head.m][cas.head.n] = 1;
		if ( can_go_north && !(cr & NORTH) )
		{
			Castle nc = cas;
			nc.head.n--;
			CastleResult res = get_number_modules_in_room( nc, depth+1, rooms );
			max += res.res;
			cas.visited = res.visited;
		}
		if ( can_go_south && !(cr & SOUTH) )
		{
			Castle nc = cas;
			nc.head.n++;
			CastleResult res = get_number_modules_in_room( nc, depth+1, rooms );
			max += res.res;
			cas.visited = res.visited;
		}
		if ( can_go_west && !(cr & WEST) )
		{
			Castle nc = cas;
			nc.head.m--;
			CastleResult res = get_number_modules_in_room( nc, depth+1, rooms );
			max += res.res;
			cas.visited = res.visited;
		}
		if ( can_go_east && !(cr & EAST) )
		{
			Castle nc = cas;
			nc.head.m++;
			CastleResult res = get_number_modules_in_room( nc, depth+1, rooms );
			max += res.res;
			cas.visited = res.visited;
		}
		res.res = MAX(max, break_max);
		res.visited = cas.visited;
		return res;
	}
	res.res = 0;
	return res;

}

int main()
{
	fin = fopen( "castle.in", "r" );
	fout = fopen( "castle.out", "w+" );

	castle.has_modified_room = 0;
	castle.head.m = castle.head.n = 0;

	fscanf( fin, "%d %d", &castle.m, &castle.n );

	assert ((char) 11 & NORTH);
	assert ((char) 11 & WEST);
	assert ((char) 11 & SOUTH);
	assert (!((char) 11 & EAST));

	for ( int n = 0; n < castle.n; ++n )
	{
		for ( int m = 0; m < castle.m; ++m )
		{
			fscanf( fin, "%hhd", &rooms.a[m][n] );
		}
	}

	int uniques[30000][2];
	int room_count = 0,
	    largest_current_room = 0,
	    largest_room_after_wall_break = 0;

	for ( int m = 0; m < castle.m; ++m )
		for ( int n = castle.n-1; n >= 0; --n )
			if ( !start_room_set[m][n] )
				{
					Castle newcas = castle;
					newcas.head.m = m;
					newcas.head.n = n;
					CastleResult res = get_number_modules_in_room( newcas, 0, &rooms );
					int num_modules = res.res;
					largest_current_room = MAX(largest_current_room, num_modules);
					room_count++;
				}

	largest_room_after_wall_break = largest_current_room;

	int max_m = -1,
	    max_n = 1;
	char max_dir = '\0';

	for ( int m = 0; m < castle.m; ++m )
	{
		for ( int n = castle.n-1; n >= 0; --n )
		{
			char cr = rooms.a[m][n];
			// If there is north wall, break it and find the number of modules
			if ( n != 0 && cr & NORTH )
			{
				Castle newcas = castle;
				VV rr = rooms;
				newcas.head.m = m;
				newcas.head.n = n;
				rr.a[m][n] -= NORTH;
				rr.a[m][n-1] -= SOUTH;
				int num_modules = get_number_modules_in_room( newcas, 0, &rr ).res;
				if ( num_modules > largest_room_after_wall_break 
					|| num_modules == largest_room_after_wall_break && m < max_m
				  	|| num_modules == largest_room_after_wall_break && m == max_m && n > max_n )
				{
					largest_room_after_wall_break = num_modules;
					max_m = m;
					max_n = n;
					max_dir = 'N';
				}
			}
			// If east wall is breakable, break it and find the number of modules
			if ( m != castle.m-1 && cr & EAST )
			{
				Castle newcas = castle;
				VV rr = rooms;
				newcas.head.m = n;
				newcas.head.n = n;
				rr.a[m][n] -= EAST;
				rr.a[m+1][n] -= WEST;
				int num_modules = get_number_modules_in_room( newcas, 0, &rr ).res;
				if ( num_modules > largest_room_after_wall_break 
					|| num_modules == largest_room_after_wall_break && m < max_m
				  	|| num_modules == largest_room_after_wall_break && m == max_m && n > max_n )
				{
					largest_room_after_wall_break = num_modules;
					max_m = m;
					max_n = n;
					max_dir = 'E';
				}
			}
		}
	}


	fprintf( fout, "%d\n%d\n%d\n", room_count, largest_current_room, largest_room_after_wall_break );
	fprintf( fout, "%d %d %c\n", max_n+1, max_m+1, max_dir );

	fclose( fin );
	fclose( fout );

	return 0;
}

