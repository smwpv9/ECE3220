#include <stdio.h>
#include <string.h>

void tester( int* c, int k ) {
	printf( "x[%d] = %d\n", k, c[ k ] );
	c[ 999 ] = 1309;  // Reduced index from 10000 to 999.
}

int main( int argc, char* argv[ ] ) {
	int i = 0, j, k;
	int x[ 1000 ];

	while( i < 1000 ) {
		x[ i ] = i;
		i++;
	}

	printf( "Enter an integer between 0 to 999: " );
	fflush( stdout );
	scanf( "%d", &k );

	tester( x, k );
	return 0; // added a return.
}