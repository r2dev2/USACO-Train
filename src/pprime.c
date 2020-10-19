/*
ID: ronak.b1
LANG: C
TASK: pprime
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

FILE *fin, *fout;

int pprimes[20000];
int a, b, p_l;

int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}


char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

char is_prime( int num )
{
	for ( int i = 2; i*i <= num; ++i )
		if ( num % i == 0 )
			return 0;
	return 1;
}

void add_num( int num )
{
	if ( num >= a && num <= b && is_prime( num ) )
	{
		fprintf( fout, "%d\n", num );
		pprimes[p_l] = num;
		p_l++;
	}
}

void generate_even( int min, int max )
{
	char nonreversed[10];
	char combined[20];
	for ( int i = min; i <= max; ++i )
	{
		strcpy( nonreversed, "" );
		strcpy( combined, "" );
		sprintf( nonreversed, "%d", i );
		sprintf( combined, "%d%s", i, strrev( nonreversed ) );
		int num; sscanf( combined, "%d", &num );
		add_num( num );
	}
}

void generate_odd( int min, int max )
{
	char nonreversed[10];
	char combined[20];
	for ( int i = min; i <= max; ++i )
	{
		strcpy( nonreversed, "" );
		strcpy( combined, "" );
		sprintf( nonreversed, "%d", i );
		sprintf( combined, "%d%s", i, strrev( nonreversed ) + 1 );
		int num; sscanf( combined, "%d", &num );
		add_num( num );
	}
}

void generate_odd_even( int min, int max )
{
	generate_odd( min, max );
	generate_even( min, max );
}

int main()
{
	fin = fopen( "pprime.in", "r" );
	fout = fopen( "pprime.out", "w+" );

	fscanf( fin, "%d %d", &a, &b );

	generate_odd_even(1, 9);
	generate_odd_even(10, 99);
	generate_odd_even(100, 999);
	generate_odd_even(1000, 9999);

	fclose( fin );
	fclose( fout );

	return 0;
}

