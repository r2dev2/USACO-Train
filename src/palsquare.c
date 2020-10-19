/*
ID: ronak.b1
LANG: C
TASK: palsquare
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
#define N2C(n) ( n < 10 ? '0' + n : 'A' + n - 10 )


int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}

void to_base( int base, int num, char *output )
{
	char buff[50];
	if ( num < base )
	{
		sprintf( buff, "%c%s", N2C( num ), output );
		strcpy( output, buff );
	}
	else
	{
		sprintf( buff, "%c%s", N2C( num % base ), output );
		strcpy( output, buff );
		to_base( base, num/base, output );
	}
}

char is_palindrome( char *str )
{
	int len = strlen( str );
	for ( int i = 0; i < len; ++i )
		if ( str[i] != str[len-i-1] )
			return 0;
	return 1;
}

int main()
{
	FILE *fin = fopen( "palsquare.in", "r" );
	FILE *fout = fopen( "palsquare.out", "w+" );


	int B;
	char squared[50];
	char num[50];
	fscanf( fin, "%d", &B );

	char buff[50];
	char correct[50];

	to_base( 10, 265, buff );
	strcpy( correct, "265" );

	assert( !strcmp(buff, correct) );

	strcpy( buff, "" );
	to_base( 16, 10, buff );
	strcpy( correct, "A" );

	assert( !strcmp(buff, correct) );

	for ( int n = 1; n <= 300; ++n )
	{
		strcpy( squared, "" );
		strcpy( num, "" );
		to_base( B, n*n, squared );
		if ( is_palindrome( squared ) )
		{
			to_base( B, n, num );
			fprintf( fout, "%s %s\n", num, squared );
		}
	}

	fclose( fin );
	fclose( fout );

	return 0;
}

