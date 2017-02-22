/*	ECE 3220
	Lab 4 Part 1
	Shayne Wadle
	*/

/*Return value meanings
	0 - success
	1 - value before option argument
	2 - no option matches argument
	3 - improper value for option
	4 - no data file of that name
	5 - incorrect file name for -r
	*/

//Includes & defines
#include <stdio.h>
#include <stdlib.h>

//prototypes
void manual( void );
int* open( int num);
void offset( int* data, double off, int num );
void scale( int* data, double scale, int num );
short copy( int* data, char* name );
double average( int* data );
int maximum( int* data );
void statistics( int* data, int num );
void center( int* data, int num );
void normal( int* data, int num );


int main( int argc, char** argv )
{
	if( argc == 1 )
	{
		manual( );
		return 2;
	}
	
	double scaleNum = 0;
	double* offsetNum = NULL;
	int dataFile = -1;
	char* name = NULL;
	short count = 1;

	short stats = 0;
	short cent = 0;
	short norm = 0;

	while( count < argc )
	{
		if( argv[ count ][ 0 ] == '-' )
		{
			if( argv[ count ][ 2 ] == '\0' )
			{
				switch( argv[ count ][ 1 ] )
				{
				case 'n': {
					count++;
					if( count >= argc )
					{
						printf( "Improper usage. -n needs a value in [1,99]\n" );
						return 3;
					}
					dataFile = (int) atoi( argv[ count ] );
					if( dataFile <= 0 || 99 < dataFile )
					{
						printf( "Improper usage. Value for -n is not in [1,99]\n" );
						return 3;
					} // else it is proper input.
					break; }
				case 'o': {
					count++;
					if( count >= argc )
					{
						printf( "Improper usage. Value for -o requires a double with nothing after it\n" );
						return 3;
					}
					char* end;
					offsetNum = (double*) malloc( sizeof( double ) );
					*offsetNum = strtod( argv[ count ], &end );
					if( *end != '\0' )
					{
						printf( "Improper usage. Value for -o requires a double with nothing after it\n" );
						free( end );
						free( offsetNum );
						return 3;
					}// else it is proper input.
					break; }
				case 's': {
					count++;
					if( count >= argc )
					{
						printf( "Improper usage. Value for -s requires a double that is not zero with nothing after it\n" );
						return 3;
					}
					char* end = NULL;
					scaleNum = strtod( argv[ count ], &end );
					if( *(end) != '\0' || scaleNum == 0 )
					{
						printf( "Improper usage. Value for -s requires a double that is not zero with nothing after it\n" );
						return 3;
					} // else it is proper input.
					break; }
				case 'r': {
					count++;
					if( count >= argc )
					{
						printf( "Improper usage.  Value for -r must be a valid file name.\n" );
						return 3;
					}
					name = argv[ count ];
					break; }
				case 'h': {
					manual( );
					break; }
				case 'S': {
					stats = 1;
					break; }
				case 'C': {
					cent = 1;
					break; }
				case 'N': {
					norm = 1;
					break; }				
				default: {
					printf( "Improper usage. No options match %s\n./a.exe <option> <value>\n-h for manual", argv[ count ] );
					return 2;
					break; }
				}
			}
			else
			{
				printf( "Improper usage. No options match %s\n./a.exe <option> <value>\n-h for manual",argv[count] );
				return 2;
			}
		}
		else
		{
			printf( "Improper usage\n./a.exe -<option> <value>\n-h for manual\n" );
			return 1;
		}
		count++;
	}


	int* data = open( dataFile );
	if( data == NULL )
	{
		printf( "Data file not found\n");
		return 4;
	}

	if( offsetNum != NULL )
	{
		offset( data, *offsetNum, dataFile );
		free( offsetNum );
	}
	if( scaleNum != 0 )
	{
		scale( data, scaleNum, dataFile );
	}
	if( name != NULL )
	{
		if( copy( data, name ) != 0 )
		{
			printf( "Filename for -r is not allowed\n" );
			return 5;
		}
	}
	if( stats == 1 )
		statistics( data, dataFile );
	if( cent == 1 )
		center( data, dataFile );
	if( norm == 1 )
		normal( data, dataFile );

	free( data );
	
	return 0;
}

void manual( void )
{
	printf( "Format for usage: ./a.exe <option> <value>\n" );
	printf( "\tOptions. \tValue Type\tFunction\n" );
	printf( "\t-n\t\tInt [1,99]\tRepresents the file num of raw data. This will truncate\n" );
	printf( "\t-o\t\tDouble\t\tOffset raw data and place into a new file\n" );
	printf( "\t-s\t\tDouble != 0\tScale raw data and place into a new file\n" );
	printf( "\t-r\t\tString\t\tCopies raw data to new file with name of <value>\n" );
	printf( "\t-h\t\tnone\t\tDisplays this manual\n\n" );
	return;
}
int* open( int num )
{
	char* fileName = (char*)malloc(15 * sizeof(char));
	if( sprintf( fileName, "Raw_data_%02d.txt", num ) != 15 )
	{
		free( fileName );
		return NULL;
	}
	FILE* in = fopen( fileName, "r" );
	if( in == NULL )
	{
		free( fileName );
		return NULL;
	}
	int size = -1;
	fscanf( in, "%d", &size );
	if( size < 0 )
	{
		free( fileName );
		return NULL;
	}
	int* array = (int*) malloc( ( size + 2 ) * sizeof( int ) );
	array[ 0 ] = size;

	short i;
	for( i = 1; i < size+2; i++ )
	{
		fscanf( in, "%d", ( array + i ) );
	}
	
	fclose( in );
	free( fileName );
	return array;
}
void offset( int* data, double off, int num )
{
	char* fileName = (char*) malloc( 18 * sizeof( char ) );
	if( sprintf( fileName, "Offset_data_%02d.txt", num ) != 18 )
	{
		free( fileName );
		return;
	}
	FILE* out = fopen( fileName, "w" );
	if( out == NULL )
	{
		free( fileName );
		return;
	}
	fprintf( out, "%d %.4f\n", *data, ( double ) *( data + 1 ) + off );
	
	short i;
	for( i = 2; i < *data + 2; i++ )
	{
		fprintf( out, "%.4f\n", (double) *( data + i ) +off );
	}

	fclose( out );
	free( fileName );
	return;
}
void scale( int* data, double scale, int num )
{
	char* fileName = (char*) malloc( 18 * sizeof( char ) );
	if( sprintf( fileName, "Scaled_data_%02d.txt", num ) != 18 )
	{
		free( fileName );
		return;
	}
	FILE* out = fopen( fileName, "w" );
	if( out == NULL )
	{
		free( fileName );
		return;
	}
	fprintf( out, "%d %.4f\n", *data, ( double ) *( data + 1 ) * scale );

	short i;
	for( i = 2; i < *data + 2; i++ )
	{
		fprintf( out, "%.4f\n", ( double ) *( data + i ) * scale );
	}

	fclose( out );
	free( fileName );
	return;
}
short copy( int* data, char* name )
{
	FILE* out = fopen( name, "w" );
	if( out == NULL )
	{
		return 1;
	}
	fprintf( out, "%d %d\n", *data, *( data + 1 )  );

	short i;
	for( i = 2; i < *data + 2; i++ )
	{
		fprintf( out, "%d\n", *( data + i ) );
	}

	fclose( out );
	return 0;
}
double average( int* data )
{
	short i = 0;
	double sum = 0;
	for( i = 0; i < *( data ); i++ )
		sum += *( data + i + 2 );
	return sum / *( data );
}
int maximum( int* data )
{
	short i = 0;
	short maxIndex = 0;
	for( i = 0; i < *( data ); i++ )
		if( *( data + 2 + maxIndex ) < *( data + 2 + i ) )
			maxIndex = i;
	return *( data + 2 + maxIndex );
}
void statistics( int* data, int num )
{
	char* fileName = (char*) malloc( 22 * sizeof( char ) );
	if( sprintf( fileName, "Statistics_data_%02d.txt", num ) != 22 )
	{
		free( fileName );
		return;
	}
	FILE* out = fopen( fileName, "w" );
	if( out == NULL )
	{
		free( fileName );
		return;
	}
	fprintf( out, "%.4f %d\n", average(data),maximum(data) );
	
	fclose( out );
	free( fileName );
	return;
}
void center( int* data, int num )
{
	char* fileName = (char*) malloc( 20 * sizeof( char ) );
	if( sprintf( fileName, "Centered_data_%02d.txt", num ) != 20 )
	{
		free( fileName );
		return;
	}
	FILE* out = fopen( fileName, "w" );
	if( out == NULL )
	{
		free( fileName );
		return;
	}
	double off = -1 * average( data );
	fprintf( out, "%d %.4f\n", *data, ( double ) *( data + 1 ) + off );

	short i;
	for( i = 2; i < *data + 2; i++ )
	{
		fprintf( out, "%.4f\n", ( double ) *( data + i ) + off );
	}

	fclose( out );
	free( fileName );
	return;
}
void normal( int* data, int num )
{
	char* fileName = (char*) malloc( 22 * sizeof( char ) );
	if( sprintf( fileName, "Normalized_data_%02d.txt", num ) != 22 )
	{
		free( fileName );
		return;
	}
	FILE* out = fopen( fileName, "w" );
	if( out == NULL )
	{
		free( fileName );
		return;
	}
	double scale = 1 / *( data + 1 );
	fprintf( out, "%d %.4f\n", *data, ( double ) *( data + 1 ) * scale );

	short i;
	for( i = 2; i < *data + 2; i++ )
	{
		fprintf( out, "%.4f\n", ( double ) *( data + i ) * scale );
	}

	fclose( out );
	free( fileName );
	return;
}
/*NOTES
	for # input check ## or 0# or # itself
	-n is file name
	-o is offset file values to a new value
	^ both +/- values accepted
	-s is multiply by an offset +/- again
	-r rename the false changed
	-h give the help info

	-S get statistics (ave, max)
	-C offset the file to mean of 0
	-N range zero and one all values.  Calc max and scale by 1/max.

	Do all error check in arg then run program
	*/