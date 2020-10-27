/*
ID: ronak.b1
LANG: C
TASK: nocows
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

#define MAXM 251
#define MAXN 151
#define MOD 9901

FILE *fin, *fout;
int N, K;
int dp[MAXM][MAXN];

int compare_int( const void *a, const void *b )
{
	return *((int*) a) - *((int*) b);
}

int main()
{
	fin = fopen( "nocows.in", "r" );
	fout = fopen( "nocows.out", "w+" );

	fscanf( fin, "%d %d", &N, &K );


	for ( int i = 1; i < MAXN; ++i )
		dp[1][i] = 1;

	for ( int k = 1; k <= K; ++k )
	{
		for ( int n = 1; n <= N; n += 2 )
		{

			for ( int nn = 1; nn < n; nn += 2 )
			{
				dp[n][k] += dp[nn][k - 1] * dp[n - nn - 1][k - 1];
			}
			dp[n][k] %= MOD;
		}
	}


	fprintf( fout, "%d\n", (int) ((dp[N][K] - dp[N][K - 1] + MOD) % MOD) );

	fclose( fin );
	fclose( fout );

	return 0;
}

