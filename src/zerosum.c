/*
ID: ronak.b1
LANG: C
TASK: zerosum
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
int N, s_l;
char sequences[7000][20];

int compare_int( const void *a, const void *b )
{
	return *((int*) a) - *((int*) b);
}

int compare_string( const void *a, const void *b )
{
	return strcmp( (char *) a, (char *) b );
}

static inline int get_operator_pos( int num )
{
	return num * 2 - 1;
}

int get_sum( const char *str )
{
	const char *end = str + strlen( str );
	char buff[10] = "";
	int buff_l = 0;
	int sum = 0;
	int num;
	for ( const char *c = str; c < end; ++c )
	{
		if ( *c == '+' || *c == '-' )
		{
			sscanf( buff, "%d", &num );
			strcpy( buff, "" );
			sum += num;

			buff[0] = *c;
			buff[1] = '\0';
			buff_l = 1;
		}
		else if ( *c != ' ' )
		{
			buff[buff_l] = *c;
			buff[buff_l + 1] = '\0';
			buff_l++;
		}
	}
	sscanf( buff, "%d", &num );
	return sum + num;
}

void generate( char *str, int pos )
{
	if ( pos == N )
	{
		int sum = get_sum( str );
		if ( sum == 0 )
		{
			strcpy( sequences[s_l], str );
			s_l++;
		}
	}
	else
	{
		int op = get_operator_pos( pos );
		generate( str, pos + 1 );
		str[op] = '+';
		generate( str, pos + 1 );
		str[op] = '-';
		generate( str, pos + 1 );
		str[op] = ' ';
	}
}

int main()
{
	fin = fopen( "zerosum.in", "r" );
	fout = fopen( "zerosum.out", "w+" );

	fscanf( fin, "%d", &N );

	char buff[20] = {0};

	for ( int i = 1; i <= N; ++i )
	{
		int op = get_operator_pos( i );
		buff[op - 1] = '0' + i;
		buff[op] = ' ';
	}
	buff[get_operator_pos( N )] = '\0';
	printf( "'%s'\n", buff );


	generate( buff, 1 );

	qsort( sequences, s_l, sizeof( sequences[0] ), compare_string );

	for ( int i = 0; i < s_l; ++i )
	{
		fprintf( fout, "%s\n", sequences[i] );
	}

	fclose( fin );
	fclose( fout );

	return 0;
}

