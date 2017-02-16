/*	ECE 3220
	Lab 4 Part 1
	Shayne Wadle
	*/

/*Return value meanings
	0 - success
	1 - value before option argument
	2 - no option matches argument
	3 - improper value for option*/

//Includes & defines
#include <stdio.h>

//prototypes
void manual( void );
double* open( int num);
void offset( double* data, double off, int num );
void scale( double* data, double scale, int num );
void copy( double* data, char* name );


int main( int argc, char** argv )
{
	if( argc == 1 )
	{
		manual( );
	}
	else
	{
		double scale = 0;
		double* offset = NULL;
		int data = -1;
		char* name = NULL;
		short count = 1;

		while( count < argc )
		{
			if( argv[ count ][ 0 ] == '-' )
			{
				if( argv[ count ][ 2 ] == '\0' )
				{
					switch( argv[ count ][ 1 ] )
					{
					case 'n':
						count++;
						data = (int) atoi( argv[ count ] );
						if( data <= 0 || 99 < data )
						{
							printf( "Improper usage. Value for -n is not in [1,99]\n" );
							return 3;
						} // else it is proper input.
						break;
					case 'o':
						count++;
						char* end;
						offset = (double*) malloc( sizeof( double ) );
						*offset = strtod( argv[ count ], &end );
						if( end != NULL )
						{
							printf( "Improper usage. Value for -o requires a double with nothing after it\n" );
							free( end );
							free( offset );
							return 3;
						}// else it is proper input.
						break;
					case 's':
						count++;
						char* end;
						scale = strtod( argv[ count ], &end );
						if( end != NULL || scale == 0 )
						{
							printf( "Improper usage. Value for -s requires a double that is not zero with nothing after it\n" );
							return 3;
						} // else it is proper input.
						break;
					case 'r':
						count++;
						name = argv[ count ];
						break;
					case 'h':
						manual( );
						break;
					default:
						printf( "Improper usage. No options match %s\n./a.exe <option> <value>\n-h for manual", argv[ count ] );
						return 2;
						break;
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
	}
	return 0;
}

void manual( void )
{
	printf( "Format for usage: ./a.exe <option> <value>\n" );
	printf( "\tOptions. \tValue Type\tFunction\n" );
	printf( "\t-n\tInt [1,99]\tRepresents the file num of raw data\n" );
	printf( "\t-o\tDouble\tOffset raw data and place into a new file\n" );
	printf( "\t-s\tDouble != 0\tScale raw data and place into a new file\n" );
	printf( "\t-r\tString\tCopies raw data to new file with name of <value>\n" );
	printf( "\t-h\tnone\tDisplays this manual\n\n" );
	return;
}
double* open( int num )
{
	char* name 
}
void offset( double* data, double off, int num )
{
	return;
}
void scale( double* data, double scale, int num )
{
	return;
}
void copy( double* data, char* name )
{
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