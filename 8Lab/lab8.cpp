/*	Shayne Wadle
	Lab 8
	ECE 3220
	*/

//Includes
#include <iostream>
#include <string>
#include <stack>
using namespace std;

//Classes
class message {
protected:
	string word;
public:
	message( );
	message( string m );
	~message( );
	virtual void print( );
};
class morseCodeMessage : public message {
private:
	string morse;
	void translate( );
public:
	morseCodeMessage(string m );
	~morseCodeMessage( );
	void print( );
};
class messageStack {
private:
	stack<message*> top;
public:
	messageStack( message* m );
	~messageStack( );
	void push( message* m );
	message* pop( );
	void print_stack( );
};

//prototypes


//---------------- Functions ------------------------
//---------------- Message --------------------------
message::message( )
{
	word = "";
}
message::message( string m )
{
	word = m ;
}
message::~message( )
{

}
void message::print( )
{
	cout << word << endl;
}


//----------------- morseCodeMessage ----------------
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
						"-.--.-","",      "-.--.-" };				 //{ , | , } ,

	for( int i = 0; i < word.length(); i++ )
		if( '0' <= word.at(i) && word.at(i) <= '}' )
			morse += code[ word[ i ] - 48 ] + " ";
		else
			morse += "\t";
	return;
}
morseCodeMessage::morseCodeMessage(string m) : message(m)
{
	morse = "";
	translate( );
}
morseCodeMessage::~morseCodeMessage( )
{
}
void morseCodeMessage::print( )
{
	cout << word << endl;
	cout << morse << endl;
}
//----------------- messageStack --------------------
messageStack::messageStack( message* m )
{
	top.push( m );
}
messageStack::~messageStack( )
{
	while( !top.empty( ) )
		top.pop( );
}
void messageStack::push( message* m )
{
	top.push( m );
}
message* messageStack::pop( )
{
	message* m = top.top( );
	top.pop( );
	return m;
}
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

//------------------- other  ------------------------


//------------------- Main ---------------------------------
int main( void )
{
	message one;
	message two( "Yay is it coded?" );
	morseCodeMessage three( "SOS" );

	messageStack list( &one );
	list.push( &two );
	list.push( &three );
	list.push( new message("YYAAYY"));

	list.print_stack( );
	list.pop( );
	list.print_stack( );

	cout << "-----------------------------------" << endl;
	two.print( );
	three.print( );
	return 0;
}