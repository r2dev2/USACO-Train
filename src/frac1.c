/*
ID: ronak.b1
LANG: C++
TASK: frac1
*/

#include <assert.h>
#include <algorithm>
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

struct Fraction {
	int num;
	int den;
	float f;
};


int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}

int compare_fraction( const void *a, const void *b )
{
	float diff = ((struct Fraction*)a)->f - ((struct Fraction*)b)->f;
	if ( diff > 0.0 )
		return 1;
	else
		return -1;
}

// Compare two floating points for equality
int feq( float f1, float f2 )
{
	return abs( f1 - f2 ) < .001;
}

void simplify_fraction( int *num, int *den )
{
	int gcd = std::__gcd( *num, *den );
	*num /= gcd;
	*den /= gcd;
}

int main()
{
	fin = fopen( "frac1.in", "r" );
	fout = fopen( "frac1.out", "w+" );

	int N;
	int frac_count = 0;
	struct Fraction fracs[30000];
	char components[161][161];

	fscanf( fin, "%d", &N );

	for ( int d = 1; d <= N; ++d )
	{
		for ( int n = 0; n <= d; ++n )
		{
			struct Fraction new_frac = { .num = n, .den =d, .f = (float) n / (float) d };
			simplify_fraction( &new_frac.num, &new_frac.den );
			if ( !components[new_frac.num][new_frac.den] )
			{
				components[new_frac.num][new_frac.den] = 1;
				fracs[frac_count] = new_frac;
				frac_count++;
			}
		}
	}

	qsort( fracs, frac_count, sizeof(struct Fraction), compare_fraction );

	for ( struct Fraction *f = fracs; f < fracs + frac_count; ++f )
		fprintf( fout, "%d/%d\n", f->num, f->den );


	fclose( fin );
	fclose( fout );

	return 0;
}

