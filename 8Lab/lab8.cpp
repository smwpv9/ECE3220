/*	Shayne Wadle
	Lab 8
	ECE 3220
	*/

//---------------- Includes -------------------------
#include <iostream>
#include <string>
#include <stack>
using namespace std;

//---------------- Classes --------------------------
//A basic message that holds a string
class message {
protected:
	string word;
public:
	message( );
	message( string m );
	~message( );
	virtual void print( );
};
//A message that holds a string and the 
//translation of that string in morse code
class morseCodeMessage : public message {
private:
	string morse;
	void translate( );
public:
	morseCodeMessage(string m );
	~morseCodeMessage( );
	void print( );
};
//A stack that holds messages. 
//dynamic so that the print functions for morseCodeMessages.
class messageStack {
private:
	stack<message*> top;
public:
	messageStack( message* m );
	~messageStack( );
	void push( message* m );
	message pop( );
	void print_stack( );
};

//---------------- Prototypes -----------------------


//---------------- Functions ------------------------
//---------------- Message --------------------------
/*	Default constructor
	Sets 'word' to its zero value
	*/
message::message( )
{
	word = "";
}
/*	Parametric constructor
	Sets 'word' to the passed argument
	*/
message::message( string m )
{
	word = m ;
}
/*	Deconstructor
	Nothing is dynamically allocated in the constructors so nothing needs to be deleted here.
*/
message::~message( )
{

}
/*	Public function
	Prints 'word' with a newline at the end.
*/
void message::print( )
{
	cout << word << endl;
}
//---------------- morseCodeMessage -----------------
/*	Private function
	Translates 'word' according to morse code available.
	Any code that does not have a translation is removed.
*/
void morseCodeMessage::translate( )
{
	string code[] =    {  "-----", ".----", "..---", "...--", "....-", //0 , 1 , 2 , 3 , 4
						".....", "-....", "--...", "---..", "----.", //5 , 6 , 7 , 8 , 9
						"---...","",	  "",	   "-...-",	"",		 //: , ; , < , = , >
						"..--..",".--.-.",".-",    "-...",	"-.-.",	 //? , @ , A , B , C
						"-..",   ".",     "..-.",  "--.",   "....",	 //D , E , F , G , H
						"..",    ".---",  "-.-",   ".-..",  "--",	 //I , J , K , L , M
						"-.",    "---",   ".--.",  "--.-",  ".-.",	 //N , O , P , Q , R
						"...",   "-",     "..-",   "...-",  ".--",	 //S , T , U , V , W
						"-..-",  "-.--",  "--..",  "-.--.-","-..-.", //X , Y , Z , [ , slash
						"-.--.-","",      "",      "",      ".-",	 //] , ^ , _ , ` , a
						"-...",  "-.-.",  "-..",   ".",	    "..-.",	 //b , c , d , e , f
						"--.",   "....",  "..",    ".---",  "-.-",	 //g , h , i , j , k
						".-..",  "--",    "-.",    "---",   ".--.",	 //l , m , n , o , p
						"--.-",  ".-.",   "...",   "-",     "..-",	 //q , r , s , t , u
						"...-",  ".--",   "-..-",  "-.--",  "--..",	 //v , w , x , y , z
						"-.--.-","",      "-.--.-" };				 //{ , | , }

	for( int i = 0; i < word.length( ); i++ )
	{
		//if the character is found in the table use it.
		if( '0' <= word.at( i ) && word.at( i ) <= '}' )
			morse += code[ word[ i ] - 48 ] + " ";
		//Otherwise check if it is a space and use a table to indicate it.
		else if( word.at( i ) == ' ' )
			morse += "\t";
		//Otherwise omit it from translation.
		else
			morse += "";
	}
	return;
}
/*	Parametric constructor
	First calls parent constructor
	Then initiallizes 'morse' and calls 'translate'
*/
morseCodeMessage::morseCodeMessage(string m) : message(m)
{
	morse = "";
	translate( );
}
/*	Deconstructor
	Nothing is dynamically allocated in the constructors so nothing needs to be deleted.
*/
morseCodeMessage::~morseCodeMessage( )
{
}
/*	Public function
	prints out 'word' and a newline
	then 'morse' and a newline
	*/
void morseCodeMessage::print( )
{
	cout << word << endl;
	cout << morse << endl;
}
//---------------- messageStack ---------------------
/*	Parametric constructor
	pushes the argument to the top of the stack
	*/
messageStack::messageStack( message* m )
{
	top.push( m );
}
/*	Deconstructor
	Empties the stack
	Nothing needs to be deleted as it was not dynamically allocated.
*/
messageStack::~messageStack( )
{
	while( !top.empty( ) )
		top.pop( );
}
/*	Public function
	pushes the argument to the top of the stack
*/
void messageStack::push( message* m )
{
	top.push( m );
}
/*	Public function
	Pops off the top of the stack
*/
message messageStack::pop( )
{
	message* m = top.top( );
	top.pop( );
	return *m;
}
/*	Public function
	prints from the top of the stack down
	by popping into temperary stack then restacking into the original.
*/
void messageStack::print_stack( )
{
	stack<message*> temp;
	while( !top.empty( ) )
	{
		
		top.top() -> print( );
		temp.push( top.top( ) );
		top.pop( );
	}
	while( !temp.empty( ) )
	{
		top.push( temp.top( ) );
		temp.pop( );
	}
}

//---------------- Other  ---------------------------
//No other functions.

//---------------- Main -----------------------------
int main( void )
{
	//Initialize some messages and morse code messages.
	message one;
	message two( "Yay is it coded?" );
	morseCodeMessage three( "SOS" );
	morseCodeMessage* four = new morseCodeMessage( "Yay done {8/ . +}" );

	//Initialize the stack and push a few messages.
	messageStack list( &one );
	list.push( &two );
	list.push( &three );
	list.push( four );

	//print the stack, change the stack, print the stack.
	list.print_stack( );
	list.pop( );
	list.print_stack( );

	cout << "-----------------------------------" << endl;
	//print more messages.
	two.print( );
	three.print( );
	delete four;
	return 0;
}