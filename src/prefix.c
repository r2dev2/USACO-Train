/*
ID: ronak.b1
LANG: C
TASK: prefix
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
int S_l, p_l; // length of S[] and primitives[][]
char S[200010];
int solve_cache[200010];
typedef struct Node Node;

struct Node {
	Node *nexts[26];
	char is_end;
};
Node primitives;

int is_in_set( const char *str );

int compare_int( const void *a, const void *b )
{
	return *((int*) a) - *((int*) b);
}

void add_primitive( const char *str )
{
	const char *end = str + strlen( str );
	Node *head = &primitives;
	for ( const char *c = str; c < end; ++c )
	{
		Node **next_head = &head->nexts[*c - 'A'];
		if ( *next_head == NULL )
		{
			*next_head = (Node *) malloc( sizeof (Node) );
			(*next_head)->is_end = 0;
		}
		head = *next_head;
	}
	head->is_end = 1;
	assert (is_in_set( str ));
}

int is_in_set( const char *str )
{
	const char *end = str + strlen( str );
	Node *head = &primitives;
	for ( const char *c = str; c < end; ++c )
	{
		Node *next_head = head->nexts[*c - 'A'];
		if ( next_head == NULL )
		{
			return 0;
		}
		head = next_head;
	}
	return head->is_end;
}

int solve( int len )
{
	if ( solve_cache[len] != 0 )
	{
		return solve_cache[len];
	}
	int max = len;
	int last_was_end = 0;

	Node *head = &primitives;
	int i;
	for ( i = len; i < S_l ; ++i )
	{
		char c = S[i];
		Node *next_head = head->nexts[c - 'A'];
		max = MAX(max, i * head->is_end);
		if ( next_head == NULL && i > len && head->is_end )
		{
			max = MAX(max, solve( i ));
			break;
		}
		else if ( next_head == NULL )
		{
			break;
		}
		else
		{
			if ( head->is_end )
			{
				max = MAX(max, solve( i ));
				last_was_end = -1;
			}
			head = next_head;
			last_was_end = last_was_end == -1 ? 1 : 0;
		}

	}
	max = MAX(max, i * head->is_end);
	solve_cache[len] = max;
	return max;
}


int main()
{
	fin = fopen( "prefix.in", "r" );
	fout = fopen( "prefix.out", "w+" );

	char buff[80] = "";
	for ( int i = 0; strcpy( buff, "" ); ++i )
	{
		fscanf( fin, "%s", buff );
		if ( buff[0] == '.' )
		{
			p_l = i;
			break;
		}
		add_primitive( buff );
	}
	for ( ; fscanf( fin, "%s", buff ) != EOF; )
	{
		strcat( S, buff );
		strcpy( buff, "" );
	}
	S_l = strlen( S );
	printf( "%d\n", S_l );

	int solution = solve( 0 );

	fprintf( fout, "%d\n", solution );

	fclose( fin );
	fclose( fout );

	return 0;
}

