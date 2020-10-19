/*
ID: ronak.b1
LANG: C
TASK: sort3
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

FILE *fin, *fout;

typedef struct {
	int a[1001];
	int len;
} Array;

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

int peek_queue( Queue *q )
{
	int v = q->beg->value;
	return v;
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


int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}


int main()
{
	fin = fopen( "sort3.in", "r" );
	fout = fopen( "sort3.out", "w+" );



	fclose( fin );
	fclose( fout );

	return 0;
}

