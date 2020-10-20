/*
ID: ronak.b1
LANG: C
TASK: runround
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

FILE *fin, *fout;
ui32 M;

typedef struct {
	char digits[9];
	char visited[9];
	char num_digits;
} Digits;

int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}

Digits get_digits( ui32 num )
{
	Digits ds = { .digits = {0}, .visited = {0}, .num_digits = 0 };
	char buff[10] = "";
	sprintf( buff, "%lu", num );
	ds.num_digits = strlen( buff );
	for ( int i = ds.num_digits - 1; i >= 0; --i, num /= 10 )
	{
		ds.digits[i] = num % 10;
	}
	if ( 0 )
	{
	for ( int i = 0; i < ds.num_digits; ++i )
		printf( "%d", ds.digits[i] );
	printf( "\n" );
	}
	return ds;
}

uint is_unique( ui32 num )
{
	char set[10] = {0};
	while ( num != 0 )
	{
		if ( set[num % 10] )
			return 0;
		set[num % 10] = 1;
		num /= 10;
	}
	return 1;
}

char is_runaround( ui32 num )
{
	Digits digs = get_digits( num );
	int head = 0;
	for ( int i = 0; i < digs.num_digits; ++i )
	{
		if ( digs.visited[head] )
		{
			return 0;
		}
		digs.visited[head]++;
		head = (head + digs.digits[head]) % digs.num_digits;
	}
	for ( int i = 1; i < digs.num_digits; ++i )
	{
		if ( !digs.visited[i] )
		{
			return 0;
		}
	}
	return head == 0;
}

int main()
{
	fin = fopen( "runround.in", "r" );
	fout = fopen( "runround.out", "w+" );

	fscanf( fin, "%lu", &M );

	assert (is_runaround( 81362 ));

	ui32 i = 0;

	for ( ++M; ; ++M, ++i )
	{
		if ( M % 10 != 0 && is_unique( M ) && is_runaround( M ) )
		{
			break;
		}
	}


	printf( "Checked %lu values\n", i );

	fprintf( fout, "%lu\n", M );

	fclose( fin );
	fclose( fout );

	return 0;
}

