/*
ID: ronak.b1
LANG: C
TASK: money
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

#define MAXM 10001

FILE *fin, *fout;
int V, N;
int values[25];
i64 dp[MAXM];

int compare_int( const void *a, const void *b )
{
	return *((int*) a) - *((int*) b);
}

int main()
{
	fin = fopen( "money.in", "r" );
	fout = fopen( "money.out", "w+" );

	fscanf( fin, "%d %d", &V, &N );

	for ( int *v = values; v < values + V; ++v )
	{
		fscanf( fin, "%d", v );
	}

	dp[0] = 1;

	for ( int *v = values; v < values + V; ++v )
	{
		for ( int n = *v; n <= N; ++n )
		{
			dp[n] += dp[n - *v];
		}
	}

	fprintf( fout, "%lld\n", dp[N] );

	fclose( fin );
	fclose( fout );

	return 0;
}

