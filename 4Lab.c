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
	
	//part one variables
	double scaleNum = 0;
	double* offsetNum = NULL;
	int dataFile = -1;
	char* name = NULL; // for the -r option
	short count = 1; //skip over the first argument
	//part two variables
	short stats = 0;
	short cent = 0;
	short norm = 0;

	while( count < argc )
	{
		if( argv[ count ][ 0 ] == '-' )//is the beginning a dash
		{
			if( argv[ count ][ 2 ] == '\0' )// is the arg only 2 characters
			{
				switch( argv[ count ][ 1 ] )
				{
				case 'n': { // set the dataFile to the value indicating the option was selected.
					count++;
					if( count >= argc ) // there is no value after the option.
					{
						printf( "Improper usage. -n needs a value in [1,99]\n" );
						return 3;
					}
					dataFile = (int) atoi( argv[ count ] );
					if( dataFile <= 0 || 99 < dataFile ) // the value is improper for this option
					{
						printf( "Improper usage. Value for -n is not in [1,99]\n" );
						return 3;
					} // else it is proper input.
					break; }
				case 'o': { // set the offset num to a double
					count++;
					if( count >= argc ) // there is no value for this option
					{
						printf( "Improper usage. Value for -o requires a double with nothing after it\n" );
						return 3;
					}
					char* end;
					offsetNum = (double*) malloc( sizeof( double ) );
					*offsetNum = strtod( argv[ count ], &end );
					if( *end != '\0' ) // the value is improper for this option
					{
						printf( "Improper usage. Value for -o requires a double with nothing after it\n" );
						free( end );
						free( offsetNum );
						return 3;
					}// else it is proper input.
					break; }
				case 's': { // set scaleNum as the value given indicating it has been asked for
					count++;
					if( count >= argc ) // there is no value.
					{
						printf( "Improper usage. Value for -s requires a double that is not zero with nothing after it\n" );
						return 3;
					}
					char* end = NULL;
					scaleNum = strtod( argv[ count ], &end );
					if( *(end) != '\0' || scaleNum == 0 ) // the value is improper for this selection
					{
						printf( "Improper usage. Value for -s requires a double that is not zero with nothing after it\n" );
						return 3;
					} // else it is proper input.
					break; }
				case 'r': { //get the new name and store it in the name indicating that the option has been asked for
					count++;
					if( count >= argc ) // there is not value for the option.
					{
						printf( "Improper usage.  Value for -r must be a valid file name.\n" );
						return 3;
					}
					name = argv[ count ];
					break; }
				case 'h': { //display the manual.
					manual( );
					break; }
				case 'S': {//indicate that the statistics have been asked for
					stats = 1;
					break; }
				case 'C': {//indicate that center has been asked for
					cent = 1;
					break; }
				case 'N': { //indicate that normalize has been asked for
					norm = 1;
					break; }				
				default: { //display error for no options match
					printf( "Improper usage. No options match %s\n./a.exe <option> <value>\n-h for manual", argv[ count ] );
					return 2;
					break; }
				}// end switch
			}// end null terminator if
			else
			{
				printf( "Improper usage. No options match %s\n./a.exe <option> <value>\n-h for manual",argv[count] );
				return 2;
			}// end null terminator else
		}// end dash if
		else
		{
			printf( "Improper usage\n./a.exe -<option> <value>\n-h for manual\n" );
			return 1;
		}//end dash or
		count++;
	}// end argument while loop


	int* data = open( dataFile ); // read in the file
	if( data == NULL ) //check if the file was not found or data was not present.
	{
		printf( "Data file not found\n");
		return 4;
	}

	if( offsetNum != NULL ) // call offset with the offset
	{
		offset( data, *offsetNum, dataFile );
		free( offsetNum );
	}
	if( scaleNum != 0 ) // call scale with the scaler
	{
		scale( data, scaleNum, dataFile );
	}
	if( name != NULL ) // call copy with the name to rename the data with
	{
		if( copy( data, name ) != 0 )
		{
			printf( "Filename for -r is not allowed\n" );
			return 5;
		}
	}
	if( stats == 1 ) // call statistics
		statistics( data, dataFile );
	if( cent == 1 ) // call center
		center( data, dataFile );
	if( norm == 1 ) // call normalize
		normal( data, dataFile );

	free( data );
	
	return 0;
}

/*Prints the manual for this program*/
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
/*Reads in the raw data file corrsponding to the number
	returns null if errored*/
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
/*Outputs the offset values into the correct file*/
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
/*Outputs the scaled values into the correct file*/
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
/*Outputs the data into the renamed file*/
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
/*Calculates the average of the data given*/
double average( int* data )
{
	short i = 0;
	double sum = 0;
	for( i = 0; i < *( data ); i++ )
		sum += *( data + i + 2 );
	return sum / *( data );
}
/*Find the maximum value within the data*/
int maximum( int* data )
{
	short i = 0;
	short maxIndex = 0;
	for( i = 0; i < *( data ); i++ )
		if( *( data + 2 + maxIndex ) < *( data + 2 + i ) )
			maxIndex = i;
	return *( data + 2 + maxIndex );
}
/*Outputs the average and max into the correct file*/
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
/*Outputs the data shifted so the average is zero to a file*/
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
/*Outputs the data scaled to be within [-1,1]*/
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
	double scale = 1 / (double)*( data + 1 );
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