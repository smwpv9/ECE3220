#include<stdio.h>
#include<string.h>
#include<malloc.h>
int main( void )
{
	char *s = (char*) malloc( 20 * sizeof( char ) ), *dyn_s;
	printf( "Enter the input string\n" );
	scanf( "%20s", s );
	dyn_s = s;
	dyn_s[ strlen( s ) ] = '\0';
	printf( dyn_s );
	return 0;
}
