#include<stdio.h>
#include<string.h>
#include<malloc.h>
int main( void )
{
	char *s = (char*) malloc( 20 * sizeof( char ) ), *dyn_s; //malloced s.
	printf( "Enter the input string\n" );
	scanf( "%20s", s );//limited the size of input.
	dyn_s = s;//didn't malloc dyn_s and just pointed dyn_s at same start.
	dyn_s[ strlen( s ) ] = '\0';
	printf( dyn_s );
	free( s );//no memory leaks.
	return 0;
}
