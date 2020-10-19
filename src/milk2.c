/*
ID: ronak.b1
LANG: C
TASK: milk2
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


int main()
{
	FILE *fin = fopen( "milk2.in", "r" );
	FILE *fout = fopen( "milk2.out", "w+" );

	int N, max_time, min_time;
	int times[5010][2];
	char time_slots[1000000] = {0};

	max_time = INT_MIN;
	min_time = INT_MAX;

	fscanf( fin, "%d", &N );
	
	for ( int i = 0; i < N; ++i )
	{
		fscanf( fin, "%d %d", &times[i][0], &times[i][1] );
		max_time = MAX( max_time, times[i][1] );
		min_time = MIN( min_time, times[i][0] );
		for ( int j = times[i][0]; j < times[i][1]; ++j )
			time_slots[j] = 1;
	}

	int max_milk = INT_MIN,
	    max_idle = INT_MIN,
	    current = time_slots[0],
	    count = 0;
	for ( int i = min_time; i < max_time; ++i )
	{
		if ( time_slots[i] == current )
			count++;
		else
		{
			if ( current )
				max_milk = MAX( max_milk, count );
			else
				max_idle = MAX( max_idle, count );
			count = 1;
			current = time_slots[i];
		}
	}

	max_milk = MAX( max_milk, count );

	fprintf( fout, "%d %d\n", MAX(max_milk, 0), MAX(max_idle, 0) );

	fclose( fin );
	fclose( fout );

	return 0;
}

