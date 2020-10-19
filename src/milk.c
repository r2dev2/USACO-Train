/*
ID: ronak.b1
LANG: C
TASK: milk
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


typedef struct {
	int milk;
	int cost;
} Farmer;

int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}

int compare_farmer( const void *a, const void *b )
{
	return ((Farmer*) a)->cost - ((Farmer*) b)->cost;
}

int main()
{
	FILE *fin = fopen( "milk.in", "r" );
	FILE *fout = fopen( "milk.out", "w+" );


	int N, M;
	Farmer farmers[5050];

	fscanf( fin, "%d %d", &N, &M );
	for ( Farmer *f = farmers; f < farmers + M; ++f )
		fscanf( fin, "%d %d", &f->cost, &f->milk );
	qsort( farmers, M, sizeof(Farmer), compare_farmer );



	int milkleft = N,
	    cost = 0;
	for ( Farmer *f = farmers; milkleft > 0 && f < farmers + M; ++f )
	{
		int received_from_farmer = milkleft - f->milk < 0 ? milkleft : f->milk;
		milkleft -= received_from_farmer;
		cost += received_from_farmer * f->cost;
	}

	fprintf( fout, "%d\n", cost );


	fclose( fin );
	fclose( fout );

	return 0;
}

