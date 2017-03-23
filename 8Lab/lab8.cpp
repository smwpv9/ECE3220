/*	Shayne Wadle
	Lab 8
	ECE 3220
	*/

//Includes
#include <iostream>
#include <string>
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
public:
	messageStack( char* m );
	void push( char* m );
	message pop( );
	void print_stack( );
};

//prototypes


//---------------- Functions ------------------------
//---------------- Message --------------------------
message::message( )
{
	word = new string( );
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
			morse += " ";
	return;
}
morseCodeMessage::morseCodeMessage(string m) : message(m)
{
	morse = new string( "" );
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

//-------------------other  --------------------------------


//------------------- Main ---------------------------------
int main( void )
{
	return 0;
}