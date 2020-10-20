/*
ID: ronak.b1
LANG: C
TASK: crypt1
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

char numset[10];
int numarr[10];

char num_is_in_set( int num );

int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}

char is_valid( int a, int b, int c, int d, int e )
{
	int numtop = a*100 + b*10 + c;

	int p1 = numtop * e,
	    p2 = numtop * d;

	int p = p1 + p2*10;

	return p <= 9999 && p1 <= 999 && p2 <= 999 && num_is_in_set(p1) && num_is_in_set(p2) && num_is_in_set(p);
}

char num_is_in_set( int num )
{
	char buff[50];
	sprintf( buff, "%d", num );
	for ( char *c = buff; *c != '\0'; ++c )
		if ( !numset[*c-'0'] )
			return 0;
	return 1;
}


int main()
{
	FILE *fin = fopen( "crypt1.in", "r" );
	FILE *fout = fopen( "crypt1.out", "w+" );

	int N, numsolutions;
	
	fscanf( fin, "%d", &N );
	for ( int i = 0; i < N; ++i )
	{
		int num;
		fscanf( fin, "%d", &num );
		numset[num] = 1;
		numarr[i] = num;
	}

	numsolutions = 0;
	for ( int a = 0; a < N; ++a )
	{
		for ( int b = 0; b < N; ++b )
		{
			for ( int c = 0; c < N; ++c )
			{
				for ( int d = 0; d < N; ++d )
				{
					for ( int e = 0; e < N; ++e )
					{
						if ( is_valid( numarr[a], numarr[b], numarr[c], numarr[d], numarr[e] ) )
						{
							numsolutions++;
						}
					}
				}
			}
		}
	}

	fprintf( fout, "%d\n", numsolutions );

	fclose( fin );
	fclose( fout );

	return 0;
}

