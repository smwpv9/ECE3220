/*	Shayne Wadle
	ECE 3220
	Lab 10 part 1
	Abstract base class
	*/

#include <iostream>
#include <cmath>
using namespace std;

//================================== Classes ===================================
/*	ABC for conic sections.
*/
class ConicSections {
protected:
	double x, y;		//location
	double majorRadius;	//radius

public:
	void move( double dx, double dy );
	virtual double area( ) = 0;
	virtual void resize( double a, double b ) throw( string ) = 0;
	virtual void display( ) = 0;
	ConicSections( double x0 = 0.0, double y0 = 0.0 );
	~ConicSections( );
};

/* derived from conic sections; circle is a main class.
*/
class Circle: public ConicSections {
public:
	int withIn( double px, double py );
	double area( );
	void resize( double a, double b) throw(string);
	void display( );
	Circle( );
	Circle( double r );
	Circle( double x0, double y0 );
	~Circle( );
};

/* derived from conic sections; ellipse is a main class
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
//Shift the position to a new position.
void ConicSections::move( double dx, double dy )
{
	x += dx;
	y += dy;
	return;
}

//Parametric constructor with default values of 0, 0
ConicSections::ConicSections( double x0, double y0 )
{
	x = x0;
	y = y0;
	majorRadius = 1;
}

//default deconstructor that does nothing currently.
ConicSections::~ConicSections( )
{
}


//================================== Circle functions ==========================
/* Identifies wheither a point is within, without or on a circle.
	0 is within
	1 is on
	2 is without
*/
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
//calculates the area
double Circle::area( )
{
	return 3.1415*majorRadius*majorRadius;
}
//REsizes the radius proportional to the first parameter
void Circle::resize( double a, double b ) throw( string )
{
	if( a <= 0 )
		throw "Radius cannot be zero or less.";
	majorRadius *= a;
}
//Displays the information of a circle.
void Circle::display( )
{
	cout << "A circle has the following: " << endl;
	cout << "Location ( " << x << ", " << y << ")" << endl;
	cout << "Radius: " << majorRadius << endl;
	cout << "Area: " << area( ) << endl << endl;
}
//Different constructor and deconstructor to give variety.
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
//Rotates the ellipse by the parameter
void Ellipse::rotate( double dtheta )
{
	theta += dtheta;
	if( theta > 180 )
		theta -= 180;
	if( theta < -180 )
		theta += 180;
}
//Calculates where the vertices are and returns them as
// a list of 8 numbers. every two make a point.
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
//calculates the area
double Ellipse::area( )
{
	return 3.1415*majorRadius*minorRadius;
}
//Resizes the major radius by a and the minor radius by b
void Ellipse::resize( double a, double b ) throw(string)
{
	if( a <= 0 || b <= 0 )
		throw "Radius cannot be zero or less.";
	majorRadius *= a;
	minorRadius *= b;
}
//Displays the information of the ellipse
void Ellipse::display( )
{
	cout << "An ellipse has the following: " << endl;
	cout << "Location ( " << x << ", " << y << ")" << endl;
	cout << "Angle: " << theta << endl;
	cout << "Radius: " << majorRadius << endl;
	cout << "Minor Radius " << minorRadius << endl;
	cout << "Area: " << area( ) << endl << endl;
}
//Different constructor and deconstructor to give variety.
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
	Circle one, two( 1, 2 );
	Ellipse three( 1, 2 );

	one.display( );
	two.display( );
	three.display( );

	one.resize( 5, 0 );
	two.move( 2, 1 );
	switch( two.withIn( 3, 4 ) )
	{
	case 0:
		cout << "(3,4) is within the circle" << endl;
		break;
	case 1:
		cout << "(3,4) is on the circle" << endl;
		break;
	case 2:
		cout << "(3,4) is outside the circle" << endl;
		break;
	default:
		cerr << "Something is wrong" << endl;
		break;
	}

	three.resize( 2, 3 );
	three.rotate( 30 );
	double* vert = three.calcVertices( );

	int i = 0;
	for( i = 0; i < 4; i ++ )
		cout << "Vertex: " << i << " is at ( " << vert[ i ] << ", " << vert[ i+1 ] << ")\n" << endl;

	//delete[ ] vert;

	one.display( );
	two.display( );
	three.display( );

	ConicSections* four = new Ellipse( -2, 1 );
	four->display( );
	four->move( -2, 1 );
	four->resize( 4, 15 );
	four->display( );


	cout << "thank you." << endl;
	
	return 0;
}