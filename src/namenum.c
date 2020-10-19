/*
ID: ronak.b1
LANG: C
TASK: namenum
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

typedef struct Letter Letter;

struct Letter {
	char l;
	Letter *parent;
	Letter *next;
};

int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}

char first_char_from_number( char num )
{
	return 'A' + 3 * ( num - 2 );
}

int get_num_continuations( FILE *fout, Letter *dict, char *numstr, int len, char *currstr )
{
	int count = 0;
	if ( len == 0 )
		return 0;

	char first = first_char_from_number( numstr[0] - '0' );
	char c = first;
	for ( char i = 0; i < 3; ++i )
	{
		if ( c == 'Q' || c == 'Z' )
			c++;
		if ( dict->next[c-'A'].l == c )
		{
			if ( len == 1 && dict->next[c-'A'].next[26].l == '\n' )
			{
				fprintf( fout, "%s%c\n", currstr, c );
				count++;
			}
			else
			{
				char newstr[15];
				sprintf( newstr, "%s%c", currstr, c );
				count += get_num_continuations( fout, dict->next + c - 'A', numstr + 1, len - 1, newstr );
			}
		}
		c++;
	}
	return count;
}

int main()
{
	FILE *fin = fopen( "namenum.in", "r" );
	FILE *fout = fopen( "namenum.out", "w+" );
	FILE *din = fopen( "dict.txt", "r" );

	char numstr[15];
	int length = 0;

	fscanf( fin, "%s", numstr );

	for ( int i = 0; numstr[i] != '\0'; ++i )
	{
		printf( "%c ", first_char_from_number( numstr[i] - '0' ) );
		length++;
	}
	printf( "\n" );


	Letter *dictionary = (Letter *) malloc( sizeof(Letter) );
	Letter *head = dictionary;

	head->next = (Letter *) calloc( 27, sizeof(Letter) );
	head->l = '\0';

	char cc;
	while ( fscanf( din, "%c", &cc ) != EOF )
	{
		if ( cc == '\n' )
		{
			head->next[26].l = '\n';
			head = dictionary;
		}
		else
		{
			if ( head->next[cc-'A'].l != cc )
			{
				head->next[cc-'A'].l = cc;
				head->next[cc-'A'].next = (Letter *) calloc( 27, sizeof(Letter) );
				head->next[cc-'A'].parent = head;
			}
			head = head->next + cc - 'A';
		}
	}


	if ( !get_num_continuations( fout, dictionary, numstr, length, "" ) )
		fprintf( fout, "NONE\n" );

	// printf( "\n%c\n", dictionary->next['K'-'A'].next['R'-'A'].next['I'-'A'].next['S'-'A'].l );

	fclose( din );
	fclose( fin );
	fclose( fout );

	return 0;
}

