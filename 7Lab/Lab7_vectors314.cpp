/*Shayne Wadle
	Lab 7
	Vector program 
	Problem 3.14
	*/

#include <iostream>
#include <vector>

using namespace std;

int main( void )
{
	vector<int> one;
	string temp;
	int num_temp;

	do {
		cout << "Please type a slew of numbers seperated by an enter\nType 'e' to exit" << endl;
		cin >> temp;
		if( temp != "e" )
		{
			num_temp = stoi( temp );//convert temp to a number
			if( num_temp != -1 )    // check if conversion was successful
				one.push_back( num_temp );
		}
	} while( temp != "e" ); //Repeat while input is not 'e'

	cout << endl;
	for( auto i : one ) // output the inputted numbers.
		cout << i << " ";
	cout << endl;

	return 0;
}