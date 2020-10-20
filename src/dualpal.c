/*
ID: ronak.b1
LANG: C
TASK: dualpal
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
	if ( str[0] == '0' )
		return 0;
	for ( int i = 0; i < len; ++i )
		if ( str[i] != str[len-i-1] )
			return 0;
	return 1;
}

int main()
{
	FILE *fin = fopen( "dualpal.in", "r" );
	FILE *fout = fopen( "dualpal.out", "w+" );


	int N, S;
	char maybepalindrome[50];
	fscanf( fin, "%d %d", &N, &S );

	char buff[50];
	char correct[50];

	to_base( 10, 265, buff );
	strcpy( correct, "265" );

	assert( !strcmp(buff, correct) );

	strcpy( buff, "" );
	to_base( 16, 10, buff );
	strcpy( correct, "A" );

	assert( !strcmp(buff, correct) );

	strcpy( buff, "" );
	to_base( 21, 2, buff );
	assert ( is_palindrome(buff) );

	int total_count = 0;

	for ( int s = S + 1; total_count < N ; ++s )
	{
		int count = 0;
		for ( int base = 2; base <= 10; ++base )
		{
			strcpy( maybepalindrome, "" );
			to_base( base, s, maybepalindrome );
			count += is_palindrome( maybepalindrome );
		}
		if ( count >= 2 )
		{
			fprintf( fout, "%d\n", s );
			total_count++;
		}
	}

	fclose( fin );
	fclose( fout );

	return 0;
}

