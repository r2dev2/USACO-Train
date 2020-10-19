/*
ID: ronak.b1
LANG: C
TASK: subset
*/

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define i64 long long
#define ui64 unsigned long long
#define uint unsigned int

#define MAX(a, b) ( a > b ? a : b )
#define MIN(a, b) ( a < b ? a : b )


FILE *fin, *fout;
int N, NT;
uint cache[800][50];
uint maxsum;

uint solve( int sum, int i )
{
	uint count = 0;
	if ( cache[sum][i] != -1 )
	{
		return cache[sum][i];
	}
	if ( sum == NT )
	{
		count++;
	}
	else if ( sum > NT )
	{
		for ( int j = N; j > i; --j )
		{
			if ( sum - j >= NT )
				count += solve( sum - j, j );
		}
	}
	cache[sum][i] = count;
	return count;
}



int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}


int main()
{
	fin = fopen( "subset.in", "r" );
	fout = fopen( "subset.out", "w+" );

	memset( cache, -1, sizeof(cache[0][0]) * 800 * 50 );

	fscanf( fin, "%d", &N );

	uint count = 0;

	for ( int i = 1; i <= N; ++i )
	{
		NT += i;
	}


	if ( NT % 2 == 0 )
	{
		NT /= 2;
		count = solve( NT * 2, 0 );
		count /= 2;
	}

	fprintf( fout, "%d\n", count );

	fclose( fin );
	fclose( fout );

	return 0;
}

