/*
ID: ronak.b1
LANG: C
TASK: lamps
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
int N, C, s_count;

typedef struct Node Node;

struct Node {
	Node *next[2];
	int value;
};

typedef struct {
	char a[101]; // 0 is on, 1 is off
	int c;
} Lamps;

Lamps final;
Node set;

void print_lamps( FILE *out, Lamps *ls );
int lamp_in_set( Lamps *ls );

int compare_int( const void *a, const void *b )
{
	return *((int*) a) - *((int*) b);
}

void add_lamp_to_set( Lamps *ls )
{
	Node *head = &set;
	for ( int i = 1; i <= N; ++i )
	{
		if ( head->next[ls->a[i]] == NULL )
		{
			head->next[ls->a[i]] = (Node *) malloc( sizeof (Node) );
		}
		assert (head != NULL);
		head = head->next[ls->a[i]];
		head->value = ls->a[i];
	}
	assert (lamp_in_set( ls ));
}

int lamp_in_set( Lamps *ls )
{
	Node *head = &set;
	for ( int i = 1; i <= N; ++i )
	{
		if ( head->next[ls->a[i]] == NULL )
		{
			return 0;
		}
		head = head->next[ls->a[i]];
	}
	return 1;
}

void __print_tree_helper( Node *n, Lamps done )
{
	done.a[done.c] = n->value;
	done.c++;
	if ( n->next[0] == NULL && n->next[1] == NULL )
	{
		print_lamps( fout, &done );
	}
	if ( n->next[0] )
	{
		__print_tree_helper( n->next[0], done );
	}
	if ( n->next[1] )
	{
		__print_tree_helper( n->next[1], done );
	}
}

void print_tree()
{
	Lamps done = { .a = {0}, .c = 0 };
	__print_tree_helper( &set, done );
}

void print_lamps( FILE *out, Lamps *ls )
{
	for ( int i = 1; i <= N; ++i )
	{
		fprintf( out, "%d", ls->a[i] );
	}
	fprintf( out, "\n" );
}

void button_1( Lamps *ls )
{
	for ( int i = 0; i <= N; ++i )
	{
		ls->a[i] = !ls->a[i];
	}
	ls->c++;
}

void button_2( Lamps *ls )
{
	for ( int i = 1; i <= N; i += 2 )
	{
		ls->a[i] = !ls->a[i];
	}
	ls->c++;
}

void button_3( Lamps *ls )
{
	for ( int i = 2; i <= N; i += 2 )
	{
		ls->a[i] = !ls->a[i];
	}
	ls->c++;
}

void button_4( Lamps *ls )
{
	for ( int k = 0; 3 * k + 1 <= N; ++k )
	{
		ls->a[3 * k + 1] = !ls->a[3 * k + 1];
	}
	ls->c++;
}

int lamps_are_final( Lamps *ls )
{
	for ( int i = 1; i <= N; ++i )
	{
		if ( final.a[i] != -1 && final.a[i] != ls->a[i] )
		{
			return 0;
		}
	}
	return 1;
}

int is_valid( Lamps *ls )
{
	return C >= ls->c && ((C - ls->c) % 2 == 0 || (C - ls->c) >= 3 ) && lamps_are_final( ls );
}

void action( Lamps *ls )
{
	// if ( is_valid( ls ) )
	Lamps new_l = *ls;
	button_1( &new_l );
	// if ( !lamp_in_set( &new_l )  && is_valid( ls ) )
	if ( !lamp_in_set( &new_l ) && is_valid( ls ) )
	{
		add_lamp_to_set( &new_l );
		s_count++;
	}
}

int main()
{
	fin = fopen( "lamps.in", "r" );
	fout = fopen( "lamps.out", "w+" );

	fscanf( fin, "%d\n%d", &N, &C );
	for ( int i = 1; i <= N; ++i )
	{
		final.a[i] = -1;
	}

	{
		int num;
		for ( fscanf( fin, "%d", &num ); num != -1; fscanf( fin, "%d", &num ) )
		{
			final.a[num] = 0;
		}

		for ( fscanf( fin, "%d", &num ); num != -1; fscanf( fin, "%d", &num ) )
		{
			final.a[num] = 1;
		}
	}

	print_lamps( stdout, &final );

	{
		Lamps working = {0};
		action( &working );
	}
	{
		Lamps working = {0};
		button_4( &working );
		action( &working );
	}
	{
		Lamps working = {0};
		button_1( &working );
		action( &working );
	}
	{
		Lamps working = {0};
		button_2( &working );
		action( &working );
	}
	{
		Lamps working = {0};
		button_3( &working );
		action( &working );
	}
	{
		Lamps working = {0};
		button_1( &working );
		button_2( &working );
		action( &working );
	}
	{
		Lamps working = {0};
		button_1( &working );
		button_3( &working );
		action( &working );
	}
	{
		Lamps working = {0};
		button_2( &working );
		button_3( &working );
		action( &working );
	}
	{
		Lamps working = {0};
		button_1( &working );
		button_2( &working );
		button_3( &working );
		action( &working );
	}

	{
		Lamps working = {0};
		button_1( &working );
		button_4( &working );
		action( &working );
	}
	{
		Lamps working = {0};
		button_2( &working );
		button_4( &working );
		action( &working );
	}
	{
		Lamps working = {0};
		button_3( &working );
		button_4( &working );
		action( &working );
	}
	{
		Lamps working = {0};
		button_1( &working );
		button_2( &working );
		button_4( &working );
		action( &working );
	}
	{
		Lamps working = {0};
		button_1( &working );
		button_3( &working );
		button_4( &working );
		action( &working );
	}
	{
		Lamps working = {0};
		button_2( &working );
		button_3( &working );
		button_4( &working );
		action( &working );
	}
	{
		Lamps working = {0};
		button_1( &working );
		button_2( &working );
		button_3( &working );
		button_4( &working );
		action( &working );
	}

	if ( s_count == 0 )
	{
		fprintf( fout, "IMPOSSIBLE\n" );
	}
	else
	{
		print_tree();
	}

	fclose( fin );
	fclose( fout );

	return 0;
}

