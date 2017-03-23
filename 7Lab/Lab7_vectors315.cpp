/*Shayne Wadle
Lab 7
Vector program
Problem 3.14
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main( void )
{
	vector<string> one;
	string temp;

	do {
		cout << "Please type a slew of strings seperated by an enter\nType 'e' to exit" << endl;
		getline( cin, temp );
		if( temp != "e" )
			one.push_back( temp );
	} while( temp != "e" ); //Repeat while input is not 'e'

	cout << endl;
	for( auto i : one ) // output the inputted numbers.
		cout << i << "\n";
	cout << endl;

	return 0;
}