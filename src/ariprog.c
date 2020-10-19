/*
ID: ronak.b1
LANG: C
TASK: ariprog
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

int N, M, largest_bisquare;
char bisquare_set[150000];

int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}

void generate_bisquare_set()
{
	for ( int p = 0; p <= M; ++p )
		for ( int q = 0; q <= M; ++q )
		{
			largest_bisquare = p*p + q*q;
			bisquare_set[p*p + q*q] = 1;
		}
}

int progression_is_valid( int a, int b )
{
	if ( a + (N-1)*b > largest_bisquare )
		return -1;
	for ( int n = 0; n < N; ++n )
		if ( !bisquare_set[a + n*b] )
			return 0;
	return 1;
}

int number_of_progressions( FILE *fout )
{
	int count = 0;
	for ( int b = 1; b <= M*M; ++b )
		for ( int a = 0; a <= M*M; ++a )
		{
			int res = progression_is_valid( a, b );
			if ( res == 1 )
			{
				fprintf( fout, "%d %d\n", a, b );
				count++;
			}
			if ( res == -1 )
				a = M*M;
		}
	return count;
}


int main()
{
	FILE *fin = fopen( "ariprog.in", "r" );
	FILE *fout = fopen( "ariprog.out", "w+" );

	fscanf( fin, "%d\n%d", &N, &M );

	generate_bisquare_set();

	if ( !number_of_progressions( fout ) )
		fprintf( fout, "NONE\n" );

	fclose( fin );
	fclose( fout );

	return 0;
}

