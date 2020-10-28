/*
ID: ronak.b1
LANG: C
TASK: concom
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

#define NCO 100

FILE *fin, *fout;

int ownership[NCO+1][NCO+1];
int owner[NCO+1][NCO+1];

int compare_int( const void *a, const void *b )
{
	return *((int*) a) - *((int*) b);
}

int add_owner( int comp )
{
	int res = 0;
	for ( int i = 1; i <= NCO; ++i )
	{
		if ( i != comp && !owner[i][comp] )
		{
			int ogown = ownership[i][comp];
			int own = 0;
			for ( int c2 = 1; c2 <= NCO; ++c2 )
			{
				own += (c2 == i || owner[i][c2]) * ownership[c2][comp];
			}
			if( own > 50 )
			{
				owner[i][comp] = 1;
				res = 1;
			}
			ownership[i][comp] = ogown;
		}
	}
	return res;
}


int main()
{
	fin = fopen( "concom.in", "r" );
	fout = fopen( "concom.out", "w+" );

	{
		int n;
		fscanf( fin, "%d", &n );
		for ( ; n; --n )
		{
			int i, j, p;
			fscanf( fin, "%d %d %d", &i, &j, &p );
			ownership[i][j] = p;
		}
	}

	int res = 1;
	while ( res )
	{
		res = 0;
		for ( int cn = 1; cn <= NCO; ++cn )
		{
			res += add_owner( cn );
		}
	}

	for ( int c1 = 1; c1 <= NCO; ++c1 )
	{
		for ( int c2 = 1; c2 <= NCO; ++c2 )
		{
			if ( c1 != c2 && owner[c1][c2] )
			{
				fprintf( fout, "%d %d\n", c1, c2 );
			}
		}
	}

	fclose( fin );
	fclose( fout );

	return 0;
}

