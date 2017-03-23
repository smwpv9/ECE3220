// Lab7_vectors.cpp
// This program shows some simple vector examples, and asks for simple tasks.
// Reference: Lippman, section 3.3

// Author: Luis Rivera

// IMPORTANT NOTE: YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG: -std=c++11
//                 OR: -std=c++0x
// Example:  g++ Lab7_vectors.cpp -o Lab7_vectors -std=c++11
//      or:  g++ Lab7_vectors.cpp -o Lab7_vectors -std=c++0x
// Some initialization methods and other things are not supported by the old standard.

#include <iostream>
#include <vector>

using namespace std;

// Main function. Shows a few examples. Complete the assignments stated in the comments.
int main( )
{
	vector<int> ivec1( 5 ), ivec2;
	vector<double> dvec1{ 5.1 }, dvec2( 5, 1.5 );
	vector<string> svec1 = { "hello", "world" };
	// vector<myClass> myCvec;	// you can have vectors of objects
	// in general: vector<Type> vec;	// vector is a template

	for( int i = 0; i < ivec1.size( ); i++ )
		cout << ivec1[ i ] << endl;
	cout << "\n------------------------------------------------------------------" << endl;

	for( auto i : ivec1 )	// This is equivalent to the above for loop
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;

	for( auto i : dvec1 )
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;

	for( auto i : dvec2 )
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;

	for( auto i : svec1 )
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;

	cout << "Original size: " << ivec2.size( ) << endl;
	ivec2.push_back( 50 );
	cout << "New size: " << ivec2.size( ) << "\nAdded element: " << ivec2[ 0 ] << endl;
	cout << "\n------------------------------------------------------------------" << endl;

	// ***********************************************************************
	// Try all the ways to initializa a vector shown in Table 3.4. Use the
	// vectors above and/or declare new vectors.
	// Some of those operations have already been used, but write your
	// own examples.

	// Do exercises 3.14 and 3.15 from Lippman (page 102)

	// Try all the vector operations shown in table 3.5. Use the vectors above
	// or define new ones. Try different types.
	// ***********************************************************************

	vector<int> one( 2 ), two( one ), three{ 4,2,1,0 };
	vector<double> four( 4, 5.25 );
	vector<int> five = { 127, 128, 50 };
	vector<int> six;

	if( two.empty( ) ) //empty() operator
		cout << "Nothing in two"<<endl;
	
	two.push_back( 4 ); // pushback() operator
	cout << two[2] << endl;
	
	one = { 4,2,1,0 }; //replacement operator.

	if( one != three ) // non equivilance operator.
		one = three;//replacement with vector operator.
	else
		cout << "one equals three" << endl;

	if( one == three ) // equivilance operator.
		cout << "one equals three" << endl;

	if( three >= five ) // comparison operator.
		cout << "three over five" << endl;
	else
		cout << "five over three" << endl;

	for( int i = 0; i < three.size( ); i++ ) //size() operator.
		if( three[ i ] == two[ 2 ] )		// [ ] operator
			cout << two[ 2 ] << " is in vector three" << endl;

	// See problems 3.14 and 3.15 in their own file.

	return 0;
}