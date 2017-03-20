/*	Shayne Wadle
	ECE 3220
	Lab 6		*/

//Includes
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;


//Classes and prototypes
class Signal{
private:
	int length;
	double max_value;
	double average;
	double* data;
	void calc_Ave( );
	void calc_Max( );


public:
	//Constructors
	Signal( );
	Signal( int fileNum );
	Signal( char* fileName );
	//Destructor
	~Signal( );
	//Other
	void offset( double off );
	void scale( double mult);
	void statistics( );
	void center( );
	void normal( );
	void Sig_info( );
	void Save_file(char* fileName );

};
void manual( );

int main( int argc, char** argv )
{
	Signal* sig;

	//Handle command line arguments
	switch( argc )
	{
	case 1: //Only the name of the executable is there so call default.
		sig = new Signal( );
		break;
	case 3: // Handle the different options
		if( argv[ 1 ][ 0 ] == '-' )//is the beginning a dash
		{
			if( argv[ 1 ][ 2 ] == '\0' )// is the arg only 2 characters
			{
				switch( argv[ 1 ][ 1 ] ) // See witch option the argument fits.
				{
				case 'n': // Is a file number
					sig = new Signal( atoi( argv[ 2 ]) );
					break; 
				case 'f': // is a file Name
					sig = new Signal( argv[ 2 ] );
					break;
				default: { //display error for no options match
					cout << "No options match argument #1" << endl;
					manual( );
					break; }
				}
			}
		}
		break;
	default: 
		cout << "Improper usage" << endl;
		manual( );
		break;
	}


	//Loop main menu
	char choice = '\0';
	do {
		//Print the menu
		cout << "\n\nPlease select an option (case sensitive):" << endl
			<< "--------------------------------------------------------------------------" << endl
			<< "n: Load in a new file to replace this one" << endl
			<< "o: Offset current data by a number" << endl
			<< "s: Scale current data by a number" << endl
			<< "h: Displays the Manual" << endl
			<< "S: Reloads the statistics of the data" << endl
			<< "C: Centralizes the data about zero" << endl
			<< "N: Normalizes the data about zero with range [-1, 1]" << endl
			<< "p: Print current statistics" << endl
			<< "q: Save" << endl
			<< "e: Quit" << endl;
		cin >> choice;

		//Do what the choice is.
		switch( choice )
		{
		case 'n': //load new file
			do {
				cout << "Do you want to:\n(1)Enter a file name\n(2)Enter a file number\n" << endl;
				cin >> choice;
			} while( choice != '1' && choice != '2' );

			if( choice == '1' )
			{
				char* name = new char[ 20 ];
				cout << "Please enter the name: " << endl;
				cin >> name;
				delete sig;
				sig = new Signal( name );
				delete name;
			}
			else //Then choice has to equal '2'
			{
				int num = 0;
				cout << "Please enter the number: " << endl;
				cin >> num;
				delete sig;
				sig = new Signal( num );
			}
			break;
		case 'o': { // offset current data
			double off = 0.0;
			cout << "Please enter the offset: " << endl;
			cin >> off;
			sig -> offset( off );
			}
			break;
		case 's': { // scale current data
			double sc = 0.0;
			cout << "Please enter the scaler: " << endl;
			cin >> sc;
			sig-> scale( sc );
			}
			break;
		case 'h': //display manual
			manual( );
			break;
		case 'S': // update statistics
			sig->statistics( );
			break;
		case 'C': // center current data
			sig->center( );
			break;
		case 'N': // normalize current data
			sig->normal( );
			break;
		case 'p': // print current statistics
			sig->Sig_info( );
			break;
		case 'q': { // save under a file name
			char* name = new char[ 20 ];
			cout << "Please enter the name: " << endl;
			cin >> name;
			sig->Save_file( name );
			delete name;
			}
			break;
		case 'e': // exit
			cout << "Have a good day\n" << endl;
			break;
		default:
			break;
		}

	} while( choice != 'e' );


	// Make sure to free the data pointed to.
	delete sig;
	return 0;
}

//Signal Private functions
/*Calculate the average and store it to the private member average*/
void Signal::calc_Ave( )
{
	if( length > 0 )
	{
		short i = 0;
		double sum = 0;
		for( i = 0; i < length; i++ )
			sum += *( data + i );
		average = sum / length;
	}
	else
		average = 0;
}
/*Calculate the maximum of the data and store in private member 'max_value' */
void Signal::calc_Max( )
{
	if( length > 0 )
	{
		short i = 0;
		short maxIndex = 0;
		for( i = 0; i < length; i++ )
			if( *( data + maxIndex ) < *( data + i ) )
				maxIndex = i;
		max_value = *( data + maxIndex );
	}
	else
		max_value = 0;
}


//Signal Public Functions
//Constructors
/*Since nothing is passed to it load in the default data
	so something is in the signal.*/
Signal::Signal( )
{
	
	fstream in;
	in.open( "Default.txt", ios::in ); // Try to open the file
	if( in.is_open( ) ) // See if the file is open
	{
		in >> length >> max_value; // if yes then load in starting values
		
		if( !( data = new double[ length ] ) )  // check to see if there is memory for that many values
		{//If not set everything to zero and exit
			cerr << "Out of memory" << endl;
			length = 0;
			data = NULL;
			return;
		}
		//Otherwise load the values in
		int i = 0;
		for( i = 0; i < length; i++ )
		{
			in >> *( data + i );
		}
		//make sure to close the open file
		in.close( );
	}
	else// if the file is not open, set everything to zero
	{
		length = 0;
		data = NULL;
	}
	return;
}
/*Take in a file number and convert it to a file name "Raw_data_nn.txt"
	And load in the data from that file.  Load zeros if file is not found*/
Signal::Signal( int fileNum )
{
	char* fileName = new char[15];
	if( sprintf( fileName, "Raw_data_%02d.txt", fileNum ) != 15 )
	{ //Check to see if the file name is of the correct format
		// if not then set everything to zero.
		length = 0;
		data = NULL;
		delete[ ] fileName;
		return;
	}


	fstream in;
	in.open( fileName, ios::in ); // try to open the file

	if( in.is_open( ) ) // see if the file is open
	{
		//if yes the load in starting values
		in >> length >> max_value;

		if( !( data = new double[ length ] ) )
		{//Check to see if there is memory for that number of values
				//if not then set everything to zero
			cerr << "Out of memory" << endl;
			length = 0;
			data = NULL;
			return;
		}

		//otherwise load in the rest of the values
		int i = 0;
		for( i = 0; i < length; i++ )
		{
			in >> *( data + i );
		}
		in.close( ); // close the open file
	}
	else
	{
		//if the file is not open to start then set everything to zero.
		length = 0;
		data = NULL;
	}
	return;
}
/*Take in a file name and load in the data from that file.
	Load zeros if file is not found*/
Signal::Signal( char* fileName )
{
	fstream in;
	in.open( fileName, ios::in ); // try to open the file
	if( in.is_open( ) )// check if the file is open
	{
		//if yes the load in starting values
		in >> length >> max_value;

		if( !( data = new double[ length ] ) )
		{//check to see if there is enough memory for that many values
			//if not then set everything to zero
			cerr << "Out of memory" << endl;
			length = 0;
			data = NULL;
			return;
		}

		//if yes then load all the rest of the values.
		int i = 0;
		for( i = 0; i < length; i++ )
		{
			in >> *( data + i );
		}
		in.close( ); // close the open file
	}
	else
	{
		// if the file is not open from the beginning then set everything to zero.
		length = 0;
		data = NULL;
	}
	return;
}
//Destructor : Free things
Signal::~Signal( )
{
	delete[ ] data;
}

//Other
void Signal::offset( double off )
{
	//Offset each data point by the value off
	short i;
	for( i = 0; i < length; i++ )
	{
		*( data + i ) += off;
	}
	statistics( );
	return;
}
void Signal::scale(double scale)
{
	//Multiple each data point by the value scale
	short i;
	for( i = 0; i < length; i++ )
	{
		*( data + i ) *= scale;
	}
	statistics( );
	return;
}
void Signal::statistics( )
{
	//Set the average and Maximum values
	calc_Ave( );
	calc_Max( );
	return;
}
void Signal::center( )
{
	//Offset the data equal to (-1) * (the average of the data)
	calc_Ave( ); //get the current average
	offset( - average );
	return;
}
void Signal::normal( )
{
	//Scale the data equal to 1 / (max of data)
	calc_Max( );//get the current max_value;
	scale( (double) 1 / max_value );
	return;
}
void Signal::Sig_info( )
{
	//Display the signal information: length, max, and average
	cout << "Properties of the signal\n"
		<< "Length: " << length << "\n"
		<< "Maximum: " << max_value << "\n"
		<< "Average: " << average << "\n" << endl;
	return;
}
void Signal::Save_file( char* fileName )
{
	//Open the file 'out'
	fstream out;
	out.open( fileName, ios::out );

	//write all the data to 'out'
	out << length << " " << max_value << endl;
	int i = 0;
	for( i = 0; i < length; i++ )
		out << *( data + i ) << endl;

	//close 'out'
	out.close( );
	return;
}

//Other functions
void manual( )
{
	cout<< "./a.exe <option> <value>\n"
		<< "\t -n \t int [01, 99]\n"
		<<"\t -f \t file name\n"
		<<"\t Neither\n" << endl;
	return;
}