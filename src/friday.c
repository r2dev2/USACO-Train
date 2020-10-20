/*
ID: ronak.b1
LANG: C
TASK: test
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


int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}


int main()
{
	FILE *fin = fopen( "INPUT.in", "r" );
	FILE *fout = fopen( "OUTPUT.out", "w+" );


	fclose( fin );
	fclose( fout );

	return 0;
}

