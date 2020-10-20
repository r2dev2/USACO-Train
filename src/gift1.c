/*
ID: ronak.b1
LANG: C
TASK: gift1
PROG: gift1
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define i64 long long
#define uint unsigned int

#define MAX(a, b) ( a > b ? a : b )
#define MIN(a, b) ( a < b ? a : b )


typedef struct {
	int money;
	char name[16];
} Person;

int compare_int( const void *a, const void *b )
{
	return *(int*) a - *(int*) b;
}

int locate_str( char *name, Person *people, int length )
{
	for ( int i = 0; i < length; ++i )
		if ( strcmp( name, people[i].name ) == 0 )
			return i;
	return -1;
}

int main()
{
	FILE *fin = fopen( "gift1.in", "r" );
	FILE *fout = fopen( "gift1.out", "w+" );


	int exit_flag = 0;
	
	Person data[11];
	int amount_people, total_money;

	fscanf( fin, "%d", &amount_people );
	for ( int i = 0; i < amount_people; ++i )
	{
		fscanf( fin, "%s", data[i].name );
		data[i].money = 0;
	}

	while ( !exit_flag )
	{
		char namebuf[16];
		int ppl_to_share;

		if ( fscanf( fin, "%s" , namebuf ) == EOF )
			break;


		fscanf( fin, "%d %d", &total_money, &ppl_to_share );

		int oglocation = locate_str( namebuf, data, amount_people );

		data[oglocation].money -= total_money;
		int received = ppl_to_share > 0 ? total_money / ppl_to_share : 0;

		for ( int i = 0; i < ppl_to_share; ++i )
		{
			char namebuf[16];
			fscanf( fin, "%s", namebuf );
			int location = locate_str( namebuf, data, amount_people );
			data[location].money += received;
			total_money -= received;
		}
		data[oglocation].money += total_money;
	}

	for ( Person *p = data; p < data + amount_people; ++p )
		fprintf( fout, "%s %d\n", p->name, p->money );


	fclose( fin );
	fclose( fout );

	return 0;
}

