/*
ID: ronak.b1
LANG: C
TASK: preface
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
int N;

typedef struct {
	int chars[200];
} Result;

int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}

Result to_roman_numerals( int n )
{
	Result res = { .chars = {0} };
	int m_s = n / 1000;
	n -= m_s * 1000;
	res.chars['M'] = m_s;

	int c_s = n / 100;
	if ( c_s == 4 )
	{
		res.chars['C'] = 1;
		res.chars['D'] = 1;
	}
	else if ( c_s == 9 )
	{
		res.chars['C'] = 1;
		res.chars['M']++;
	}
	else
	{
 		if ( c_s >= 5 )
			res.chars['D'] = 1;
		res.chars['C'] = c_s % 5;
	}
	n -= c_s * 100;

	int x_s = n / 10;
	if ( x_s == 4 )
	{
		res.chars['X'] = 1;
		res.chars['L'] = 1;
	}
	else if ( x_s == 9 )
	{
		res.chars['X'] = 1;
		res.chars['C']++; // Done
	}
	else
	{
 		if ( x_s >= 5 )
			res.chars['L'] = 1;
		res.chars['X'] = x_s % 5;
	}
	n -= x_s * 10;
	// C D M 
	// I V X

	if ( n == 4 )
	{
		res.chars['I'] = 1;
		res.chars['V'] = 1;
	}
	else if ( n == 9 )
	{
		res.chars['I'] = 1;
		res.chars['X']++;
	}
	else
	{
 		if ( n >= 5 )
			res.chars['V'] = 1;
		res.chars['I'] = n % 5;
	}
	return res;
}

void add_results( Result *dest, Result *to_add )
{
	for ( int i = 0; i < 200; ++i )
	{
		dest->chars[i] += to_add->chars[i];
	}
}

void write_result( Result *answer )
{
	char numerals[] = "IVXLCDM";
	for ( char *c = numerals; *c != '\0'; ++c )
	{
		if ( answer->chars[*c] )
		{
			fprintf( fout, "%c %d\n", *c, answer->chars[*c] );
		}
	}
}

int main()
{
	fin = fopen( "preface.in", "r" );
	fout = fopen( "preface.out", "w+" );

	fscanf( fin, "%d", &N );

	Result total = { .chars = {0} };
	for ( int i = 1; i <= N; ++i )
	{
		Result res = to_roman_numerals( i );
		add_results( &total, &res );
	}
	write_result( &total );

	fclose( fin );
	fclose( fout );

	return 0;
}

