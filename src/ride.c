/*
ID: ronak.b1
LANG: C
TASK: ride
PROG: ride
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define i64 long long
#define uint unsigned int

#define MAX(a, b) ( a > b ? a : b )
#define MIN(a, b) ( a < b ? a : b )


int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}


int main()
{
	FILE *fin = fopen( "ride.in", "r" );
	FILE *fout = fopen( "ride.out", "w+" );


	char comet_name[8];
	char group_name[8];
	
	fscanf( fin, "%s", comet_name );
	fscanf( fin, "%s", group_name );

	int comet_count = 1, group_count = 1;

	for ( char *c = comet_name; c < comet_name + 6; ++c )
	{
		if ( *c == '\0' )
			break;
		comet_count *= (int) *c - 64;
	}

	for ( char *c = group_name; c < group_name + 6; ++c )
	{
		if ( *c == '\0' )
			break;
		group_count *= (int) *c - 64;
	}

	if ( comet_count % 47 == group_count % 47 )
		fprintf( fout, "GO\n" );
	else
		fprintf( fout, "STAY\n" );

	fclose( fin );
	fclose( fout );

	return 0;
}

