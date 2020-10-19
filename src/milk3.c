/*
ID: ronak.b1
LANG: C
TASK: milk3
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


int full[3];
int filled[3];
char amount_milk_in_c[30];
char arrays_done[200000];

int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}

// Completes the bucket transaction and returns the amount of milk transferred
int fill_buckets( char bucket_to_fill, char bucket_with_to_fill )
{
	int amount_milk = filled[bucket_with_to_fill];
	if ( amount_milk > full[bucket_to_fill] - filled[bucket_to_fill] )
		amount_milk = full[bucket_to_fill] - filled[bucket_to_fill];
	filled[bucket_to_fill] += amount_milk;
	filled[bucket_with_to_fill] -= amount_milk;
	return amount_milk;
}

int hash_buckets( char bucket_being_emptied )
{
	int z = bucket_being_emptied*21*21*21,
	    a = filled[0]*21*21,
	    b = filled[1]*21,
	    c = filled[2];
	return a + b + c + z;
}

int get_number( char bucket_with_to_fill )
{
	int count = 0;
	if ( arrays_done[hash_buckets( bucket_with_to_fill )] )
	{
		// printf( "\t[%d, %d, %d] has been done\n", filled[0], filled[1], filled[2] );
		return 0;
	}
	arrays_done[hash_buckets( bucket_with_to_fill )] = 1;
	for ( char i = 0; i < 3; ++i )
	{
		if ( i != bucket_with_to_fill )
		{
			int a = filled[0],
			    b = filled[1],
			    c = filled[2];
			// printf( "trying [%d, %d, %d]\n", filled[0], filled[1], filled[2] );
			int amount = fill_buckets( i, bucket_with_to_fill );
			// printf( "led to [%d, %d, %d]\n", filled[0], filled[1], filled[2] );
			if ( filled[0] == 0 && !amount_milk_in_c[filled[2]] )
			{
				amount_milk_in_c[filled[2]] = 1;
				count++;
			}
			count += get_number( 0 ) + get_number( 1 ) + get_number( 2 );
			filled[i] -= amount;
			filled[bucket_with_to_fill] += amount;
			// assert (filled[0] == a && filled[1] == b && filled[2] == c);
		}
	}
	return count;
}

int main()
{
	FILE *fin = fopen( "milk3.in", "r" );
	FILE *fout = fopen( "milk3.out", "w+" );

	fscanf( fin, "%d %d %d", full, full+1, full+2 );
	filled[2] = full[2];


	int num_combos = get_number( 2 );

	// printf( "Received %d combinations\n", num_combos );

	int queue = -1;

	for ( int i = 0; i < 30; ++i )
		if ( amount_milk_in_c[i] )
		{
			if ( queue != -1 )
				fprintf( fout, "%d ", queue );
			queue = i;
		}

	if ( queue != -1 )
		fprintf( fout, "%d\n", queue );

	fclose( fin );
	fclose( fout );

	return 0;
}

