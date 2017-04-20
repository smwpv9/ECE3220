/*	Shayne Wadle
	ECE 3220
	Lab 10 part 1
	Abstract base class
	*/

#include <iostream>
#include <cmath>
using namespace std;

//================================== Classes ===================================
/*	
*/
class ConicSections {
protected:
	double x, y;		//location
	double majorRadius;	//radius

public:
	void move( double dx, double dy );
	virtual double area( ) = 0;
	virtual void resize( double a, double b ) throw( string ) = 0;
	virtual void display( );
	ConicSections( double x0 = 0.0, double y0 = 0.0 );
	~ConicSections( );
};

/*
*/
class Circle: public ConicSections {
public:
	int withIn( double px, double py );
	double area( );
	void resize( double a, double b) throw(string);
	Circle( );
	Circle( double r );
	Circle( double x0, double y0 );
	~Circle( );
};

/*
*/
class Ellipse: public ConicSections {
private:
	double minorRadius;
	double theta;
public:
	void rotate( double dtheta );
	double* calcVertices( );
	double area( );
	void resize( double a, double b ) throw( string );
	void display( );
	Ellipse( );
	Ellipse( double x0, double y0 );
	~Ellipse( );


};
//================================== ConicSection functions ====================
void ConicSections::move( double dx, double dy )
{
	x += dx;
	y += dy;
	return;
}

void ConicSections::display( )
{
	cout << "Location ( " << x << ", " << y << ")" << endl;
	cout << "Radius: " << majorRadius << endl;
	cout << "Area: " << area( ) << endl;
}

ConicSections::ConicSections( double x0, double y0 )
{
	x = x0;
	y = y0;
	majorRadius = 1;
}

ConicSections::~ConicSections( )
{
}


//================================== Circle functions ==========================
int Circle::withIn( double px, double py )
{
	double length = ( px - x )*( px - x ) + ( py - y )*( py - y );
	if( length > majorRadius*majorRadius )
		return 2;
	else if( length < majorRadius*majorRadius )
		return 0;
	else
		return 1;
}
double Circle::area( )
{
	return 3.1415*majorRadius*majorRadius;
}
void Circle::resize( double a, double b ) throw( string )
{
	if( a <= 0 )
		throw "Radius cannot be zero or less.";
	majorRadius *= a;
}
Circle::Circle( ) : ConicSections( 0, 0 )
{

}
Circle::Circle( double r ) : ConicSections( 0, 0 )
{
	if( r <= 0 )
		throw "Radius cannot be zero or less.";
	majorRadius = r;
}
Circle::Circle( double x0, double y0 ): ConicSections( x0, y0 )
{

}
Circle::~Circle( )
{

}


//================================== Ellipse functions =========================
void Ellipse::rotate( double dtheta )
{
	theta += dtheta;
	if( theta > 180 )
		theta -= 180;
	if( theta < -180 )
		theta += 180;
}
double* Ellipse::calcVertices( )
{
	double* vert = new double[ 8 ];

	vert[ 0 ] = majorRadius*cos( theta );
	vert[ 1 ] = majorRadius*sin( theta );
	vert[ 2 ] = -1 *minorRadius*sin( theta );
	vert[ 3 ] = minorRadius * cos( theta );
	vert[ 4 ] = -1*majorRadius *cos( theta );
	vert[ 5 ] = -1*majorRadius *sin( theta );
	vert[ 6 ] = minorRadius * sin( theta );
	vert[ 7 ] = -1*minorRadius*cos( theta );

	int i;
	for( i = 0; i < 8; i += 2 );
	{
		vert[ i ] += x;
		vert[ i + 1 ] += y;
	}
	return vert;
}
double Ellipse::area( )
{
	return 3.1415*majorRadius*minorRadius;
}
void Ellipse::resize( double a, double b ) throw(string)
{
	if( a <= 0 || b <= 0 )
		throw "Radius cannot be zero or less.";
	majorRadius *= a;
	minorRadius *= b;
}
void Ellipse::display( )
{
	cout << "Location ( " << x << ", " << y << ")" << endl;
	cout << "Angle: " << theta << endl;
	cout << "Radius: " << majorRadius << endl;
	cout << "Minor Radius " << minorRadius << endl;
	cout << "Area: " << area( ) << endl;
}
Ellipse::Ellipse( ):ConicSections( 0, 0 )
{
	minorRadius = 0.5;
	theta = 0;
}
Ellipse::Ellipse( double x0, double y0 ):ConicSections(x0,y0)
{
	minorRadius = 0.5;
	theta = 0;
}
Ellipse::~Ellipse( )
{

}
//================================== Other functions ===========================
//================================== Main ======================================
int main( void )
{
	Ellipse one( 0, 0 );
	one.rotate( 3* 3.14159/4 );
	double* vertices = one.calcVertices( );

	int i;
	for( i = 0; i < 8; i++ )
	{
		cout << vertices[ i ] << endl;
	}
	delete vertices;
	return 0;
}