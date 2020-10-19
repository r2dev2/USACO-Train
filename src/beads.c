/*
ID: ronak.b1
LANG: C
TASK: beads
*/

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define i64 long long
#define uint unsigned int

#define MAX(a, b) ( a > b ? a : b )
#define MIN(a, b) ( a < b ? a : b )


int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}

int get_length( int *arr, int *end )
{
	int color = 1,
	    color_switch = 2,
	    count = -1;
	for ( int *a = arr; a < end; ++a )
	{
		if ( *a )
		{
			color = *a;
			break;
		}
	}
	for ( int *a = arr; a < end; ++a )
	{
		if ( *a )
		{
			if ( *a != color )
			{
				color = *a;
				color_switch--;
			}
		}
		count++;
		if ( !color_switch )
		{
			return count;
		}
	}
	return count + 1;
}


int main()
{
	FILE *fin = fopen( "beads.in", "r" );
	FILE *fout = fopen( "beads.out", "w+" );


	// int *arr = (int *) calloc( length, sizeof( int ) );
	//
	// for ( int *el = arr; el < arr + length; ++el )
	char raw_necklace[355];
	int beads[710];
	int boundaries[710][2];
	int N;

	// int char_to_num[3] = { 'r', 'w', 'b' };
	int char_to_num[200];

	char_to_num['r'] = -1;
	char_to_num['w'] = 0;
	char_to_num['b'] = 1;

	fscanf( fin, "%d", &N );
	fscanf( fin, "%s", raw_necklace );

	for ( int i = 0; i < N; ++i )
	{
		int beadnum = char_to_num[raw_necklace[i]];
		beads[i] = beadnum;
		beads[i + N] = beadnum;
	}

	int current = beads[0],
	    blen = 0;

	for ( int i = 0, last_b = 0; i < 2*N; ++i )
	{
		if ( beads[i] != current )
		{
			boundaries[blen][0] = last_b;
			boundaries[blen][1] = i;
			last_b = i;
			blen++;
			current = beads[i];
		}
	}


	int max = INT_MIN+1,
	    max2 = INT_MIN;
	for ( int b = 0; b < blen; ++b )
	{
		int bb = b;
		int *beg = beads + boundaries[bb][0];
		int additional = 0;
		int ccc = get_length( beg, beads + 2*N ) + additional;
		if ( ccc >= max )
		{
			if ( ccc != max )
				max2 = max;
			max = ccc;
		}
		else if ( ccc >= max2 )
		{
			max2 = ccc;
		}
	}

	fprintf( fout, "%d\n", (max < N && max > 0) ? max : N );
	

		
	fclose( fin );
	fclose( fout );

	return 0;
}

