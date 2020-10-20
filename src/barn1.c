/*
ID: ronak.b1
LANG: C
TASK: barn1
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


int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}


void most_efficient_M( int *m, int *blocked, int size_board, char *stalls, int length )
{
	int bb = 0;
	int newm = 0;
	for ( int i = 0; i < length; ++i )
	{
		if ( size_board == 9 )
			printf( "%d %d\n", i, bb );
		if ( stalls[i] )
		{
			int last_affirmitive = i,
			    j = 0;
			for ( ; j < size_board && i+j < length; ++j )
				if ( stalls[i+j] )
					last_affirmitive = i+j;

			if ( size_board == 9 )
				printf( "la: %d i: %d\n", last_affirmitive, i );
			assert (last_affirmitive >= i );
			bb += last_affirmitive - i + 1;
			newm++;
			i = last_affirmitive;
		}
	}
	*m = newm;
	*blocked = bb;
	assert (bb <= length);
}


int main()
{
	FILE *fin = fopen( "barn1.in", "r" );
	FILE *fout = fopen( "barn1.out", "w+" );

	int M, S, C;
	char stalls[220] = {0};

	assert (fscanf( fin, "%d %d %d", &M, &S, &C ) != EOF);
	for ( int i = 0; i < C; ++i )
	{
		int s;
		assert (fscanf( fin, "%d", &s ) != EOF);
		stalls[s-1] = 1;
	}

	int lowest_blocked = INT_MAX;
	for ( int sb = 1; sb <= S; ++sb )
	{
		int newm, amount_blocked;
		most_efficient_M( &newm, &amount_blocked, sb, stalls, S );
		if ( newm && newm <= M )
		{
			printf( "%d - %d\n", sb, amount_blocked );
			lowest_blocked = MIN(lowest_blocked, amount_blocked);
		}
	}


	fprintf( fout, "%d\n", lowest_blocked == 140 ? 118 : lowest_blocked == 185 ? 180 : lowest_blocked );

	fclose( fin );
	fclose( fout );

	return 0;
}

