/*
ID: ronak.b1
LANG: C
TASK: skidesign
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

int main()
{
	FILE *fin = fopen( "skidesign.in", "r" );
	FILE *fout = fopen( "skidesign.out", "w+" );


	int N;
	int elevations[1010] = {0};
	int costs[1010] = {0};

	fscanf( fin, "%d", &N );
	for ( int *e = elevations; e < elevations + N; ++e )
		fscanf( fin, "%d", e );

	
	int min_cost = INT_MAX;

	for ( int i = 0, j = 17; j <=100; ++i, ++j )
	{
		int count_cost = 0;
		for ( int *e = elevations; e < elevations + N; ++e )
		{
			if ( *e > j )
				count_cost += (*e - j) * (*e - j);
			if ( *e < i )
				count_cost += (*e - i) * (*e - i);
		}
		min_cost = MIN(min_cost, count_cost);
	}

	fprintf( fout, "%d\n", min_cost );

	fclose( fin );
	fclose( fout );

	return 0;
}

