/*
ID: ronak.b1
LANG: C
TASK: hamming
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
int *pow_of_2;
int N, B, D;

typedef struct {
	int arr[64];
	int len;
} Solution;

Solution cache[500];
char in_cache[500];
Solution best_solution;

int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}

char hamming_distance( char a, char b )
{
	char comb = a ^ b;
	char sum = 0;
	for ( int i = 0; i < 8; ++i )
	{
		if ( comb & pow_of_2[i] )
		{
			sum++;
		}
	}
	return sum;
}

Solution solve( Solution start )
{
	if ( start.len != 0 && in_cache[start.arr[start.len - 1]] )
	{
		return cache[start.arr[start.len - 1]];
	}
	Solution best = start;
	int st = start.len != 0 ? start.arr[start.len - 1] : 1;
	if ( start.len == N )
	{
		return start;
	}
	for ( int i = st; i < pow_of_2[B]; ++i )
	{
		Solution head = start;
		char doit = 1;
		if ( head.len == 0 )
		{
			head.arr[0] = i;
			head.len = 1;
		}
		else
		{
			head.arr[head.len] = i;
			head.len++;
		}
		for ( int i = 0; i < head.len; ++i )
		{
			if ( i != head.len - 1 && hamming_distance( head.arr[i], head.arr[head.len - 1] ) < D )
			{
				doit = 0;
			}
		}
		if ( doit )
		{
		// printf( "ee\n" );
			Solution sol = solve( head );
		// printf( "eeee %d\n\n", doit );
			if ( sol.len > best.len ) // || sol.len == best.len 
			{
				best = sol;
			}
		}
	}
	if ( start.len != 0 )
	{
		cache[start.arr[start.len - 1]] = best;
		in_cache[start.arr[start.len - 1]] = 1;
	}
	return best;
}

int main()
{
	fin = fopen( "hamming.in", "r" );
	fout = fopen( "hamming.out", "w+" );

	int m2[9] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
	pow_of_2 = m2;


	fscanf( fin, "%d %d %d", &N, &B, &D );

	// B -= 1;


	printf( "%d\n", hamming_distance( 42, 30 ) );
	printf( "%d\n", pow_of_2[B] );

	best_solution.arr[0] = 0;
	best_solution.len = 1;

	Solution sol = solve( best_solution );

	fprintf( stdout, "%d\n", sol.len );
	for ( int i = 0; i < sol.len; ++i )
	{
		fprintf( fout, "%d", sol.arr[i] );
		if ( i % 10 == 9 || i == sol.len - 1 )
		{
			fprintf( fout, "\n" );
		}
		else 
		{
			fprintf( fout, " " );
		}
	}
	

	fclose( fin );
	fclose( fout );

	return 0;
}

