/*
ID: ronak.b1
LANG: C
TASK: combo
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

int N;
char map[1100000];

int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}

int hash_combo( int a, int b, int c )
{
	return a + b*101 + c*101*101;
}

int is_in( int a, int b, int c )
{
	return map[hash_combo( a, b, c )];
}

int add_delta( int num, int delta )
{
	if ( num + delta > N )
		return add_delta( num + delta - N, 0 );
	else if ( num + delta < 1 )
		return add_delta( N + (num + delta), 0 );
	else
		return num + delta;
}

int get_num( int a, int b, int c )
{
	int counter = 0;
	for ( int ad = -2; ad <= 2; ++ad )
		for ( int bd = -2; bd <= 2; ++bd )
			for ( int cd = -2; cd <= 2; ++cd )
				if ( !is_in( add_delta(a, ad), add_delta(b, bd), add_delta(c, cd) ) )
				{
					map[hash_combo( add_delta(a, ad), add_delta(b, bd), add_delta(c, cd) )] = 1;
					counter++;
				}
	return counter;
}


int main()
{
	FILE *fin = fopen( "combo.in", "r" );
	FILE *fout = fopen( "combo.out", "w+" );


	int a1, b1, c1, a2, b2, c2;
	fscanf( fin, "%d", &N );
	fscanf( fin, "%d %d %d", &a1, &b1, &c1 );
	fscanf( fin, "%d %d %d", &a2, &b2, &c2 );

	// assert (add_delta( 1, -1 ) == N);
	// assert (add_delta( 1, -2 ) == N-1);
	// assert (add_delta( N, 0 ) == N);
	// assert (add_delta( N, 1 ) == 1);
	// assert (add_delta( 1, 2 ) == 3);

	int count = 0;
	

	count += get_num( a1, b1, c1 );
	count += get_num( a2, b2, c2 );

	fprintf( fout, "%d\n", count );

	fclose( fin );
	fclose( fout );

	return 0;
}

