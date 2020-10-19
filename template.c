/*
ID: ronak.b1
LANG: C
TASK: taskname
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

int compare_int( const void *a, const void *b )
{
	return *((int*) a) - *((int*) b);
}


int main()
{
	fin = fopen( "taskname.in", "r" );
	fout = fopen( "taskname.out", "w+" );



	fclose( fin );
	fclose( fout );

	return 0;
}

