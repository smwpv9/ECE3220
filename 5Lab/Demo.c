#include<stdio.h>
#include<malloc.h>
void main( )
{
	char *a = "hey";
	free( a );
	a = (char*) malloc( 6 * sizeof( char ) );
	a = "hello\0";
	printf( "%s", a );
}