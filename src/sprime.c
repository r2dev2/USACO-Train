/*
ID: ronak.b1
LANG: C
TASK: sprime
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
#define PCL 100000000

FILE *fin, *fout;

typedef struct Node Node;

struct Node {
	int value;
	Node *next;
};

typedef struct {
	Node *beg;
	Node *end;
	int len;
} Queue;


Queue *create_queue()
{
	Queue *q = (Queue *) malloc( sizeof(Queue) );
	q->len = 0;
	return q;
}

void push_queue( Queue *q, int val )
{
	Node *n = (Node *) malloc( sizeof(Node) );
	n->value = val;
	if ( q->len )
	{
		q->end->next = n;
		q->end = n;
	}
	else
	{
		q->beg = n;
		q->end = n;
	}
	q->len++;
}

int pop_queue( Queue *q )
{
	Node *n = q->beg;
	q->beg = n->next;
	q->len--;
	int val = n->value;
	free( n );
	return val;
}


void free_queue( Queue *q )
{
	for ( int i = 0; i < q->len; ++i )
	{
		Node *n = q->beg;
		q->beg = n->next;
		free( n );
	}
	free( q );
}


char is_super_prime( int n );

int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}

char is_prime( int n )
{
	if ( n == 1 || n % 2 == 0 && n != 2 )
		return 0;
	for ( int i = 2; i*i <= n; ++i )
		if ( n % i == 0 )
			return 0;
	return 1;
}

char is_super_prime( int n )
{
	if ( n < 10 )
		return is_prime( n );
	return is_prime( n ) && is_super_prime( n / 10 );
}

int main()
{
	fin = fopen( "sprime.in", "r" );
	fout = fopen( "sprime.out", "w+" );

	int N;
	
	fscanf( fin, "%d", &N );

	assert (is_super_prime( 2333 ));
	assert (is_super_prime( 2339 ));
	assert (is_super_prime( 2393 ));
	assert (is_super_prime( 5939 ));
	assert (is_super_prime( 7333 ));

	Queue *q = create_queue();

	for ( int i = 2; i < 10; ++i )
	{
		if ( is_prime( i ) )
		{
			push_queue( q, i );
		}
	}

	// i is number of digits
	for ( int i = 2; i <= N; ++i )
	{
		int pp = (int) (pow(10, i-1));
		int up = (int) (pow(10, i));
		int beg = q->beg->value;
		for ( int l = q->len; l ; --l )
		{
			int q_num = pop_queue( q );
			// j is the first digit
			for ( int j = 1; j < 10; ++j )
			{
				if ( is_super_prime( j + q_num*10 ) )
				{
					push_queue( q, j + q_num*10 );
				}
			}
			beg = q->beg->value;
		}
	}

	while ( q->len != 0 )
		fprintf( fout, "%d\n", pop_queue( q ) );



	free_queue( q );
	fclose( fin );
	fclose( fout );

	return 0;
}

