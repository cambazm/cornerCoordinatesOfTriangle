/********************************************
 * Object Oriented Programming Assignment 1 *
 *											*
 * Student  : MEHMET CAMBAZ                 *
 * Number   : 040020365                     *
 *											*
 * Compiler : Microsoft Visual C++ 6.0      *
 * Controlled with Dev-C++ compiler			*
 ********************************************/
#include<iostream>
#include<math.h>

using namespace std;

// ************ LINE OBJECT **************
class Line { 

		double x, y, m;							// (x,y) is a point on the line, m is the slope this line

	public: 
		Line(double, double, double);			//Non-vertical line constructor
		Line(double=0, double=0);				//Vertical line constructor
		Line(const Line &);						//Copy Constructor
	
		double getX();							// returns line's x coordinate
		double getY(); 							// returns line's y coordinate
		double getM();							// returns line's slope 
	
		bool onLine(double,double);				//Point is on line?
};

// LINE'S METHODS

Line::Line(double x_point, double y_point, double slope)
{
	//cout<<"Non-vertical Line Constructor is called"<<endl;
	x = x_point;
	y = y_point;
	m = slope;
}

Line::Line(double x_point, double y_point)
{
	//cout<<"Vertical Line Constructor is called"<<endl;
	x = x_point;
	y = y_point;
	m = 4294967295;	// $FFFFFFFF, a very large value double can have, its slope is infinitive we define its slope this way
}

Line::Line(const Line &line1)
{
	//cout<<"Line Copy constructor is called"<<endl;
	x = line1.x;
	y = line1.y;
	m = line1.m;
}
double Line::getX()
{
	return x;
}

double Line::getY()
{
	return y;
}

double Line::getM()
{
	return m;
}

bool Line::onLine (double x_point, double y_point)
{
	if ( m == ((y - y_point) / (x - x_point)) )
		return true;
	else
		return false;
}


// ************ CIRCLE OBJECT **************
class Circle { 
		
		double h, k, r;	// (h,k) is center of circle, r is the radius
		
	public: 
		Circle(double, double, double);			// Circle constructor
		bool onCircle(double, double);			// Point is on circle? 
		Line getTangent(double x, double y);	// Form the tangent line at given point (x, y)

};

// CIRCLE'S METHODS 

Circle::Circle(double x_point, double y_point, double radius)
{
	//cout<<"Circle constructor is called"<<endl;
	h = x_point;
	k = y_point;
	r = radius;
}

bool Circle::onCircle(double x_point, double y_point)
{
	if( fabs(pow((x_point-h),2)+pow(y_point-k,2)-pow(r,2)) < 0.001 )	// Circle's equation is "pow((x-h), 2) + pow((y-k), 2) = pow(r, 2)
		return true;
	else
		return false;
}

Line Circle::getTangent(double x_point, double y_point)
{
	double slopeNormal, slopeTangent;

	slopeNormal = (y_point - k) / (x_point - h);

	if(slopeNormal == 0) {						// if normal to tangentline is 0, then tangent line will be perpendicular
		Line tangentline(x_point, y_point);		// tangentline is perpendicular, vertical line constructor is called

		return tangentline;
	}
	else {
		slopeTangent = (-1) / slopeNormal;		// (slope of normal line) * (slope of tangent line) = -1
		Line tangentline(x_point, y_point, slopeTangent);
	
		return tangentline;
	}
}

// ************ TRIANGLE OBJECT **************
class Triangle { 

		Line first, second, third;		// Triangle consists of 3 lines (without any two parallel lines)
	
	public: 
		Triangle(const Line &, const Line &, const Line &);
		void getCorners(); 
};

// TRIANGLE'S METHODS 

Triangle::Triangle(const Line &first_line, const Line &second_line, const Line &third_line)
{
	first = first_line;
	second = second_line;
	third = third_line;
}

void Triangle::getCorners()
{
	double ma = first.getM();
	double mb = second.getM();
	double xa = first.getX();
	double xb = second.getX();
	double ya = first.getY();
	double yb = second.getY();
	
	// intersection of line 1 and 2
	double x1 = (mb*xb - ma*xa + ya - yb) / (mb - ma);
	double y1 = ma*(x1 - xa) + ya;

	mb = third.getM();
	xb = third.getX();
	yb = third.getY();

	// intersection of line 1 and 3
	double x2 = (mb*xb - ma*xa + ya - yb) / (mb - ma);
	double y2 = ma*(x2 - xa) + ya;

	ma = second.getM();
	xa = second.getX();
	ya = second.getY();

	// intersection of line 2 and 3
	double x3 = (mb*xb - ma*xa + ya - yb) / (mb - ma);
	double y3 = ma*(x3 - xa) + ya;

	cout<<"Triangle corner point 1: \n"<<"x1: "<<x1<<"\n"<<"y1: "<<y1<<"\n\n";
	cout<<"Triangle corner point 2: \n"<<"x2: "<<x2<<"\n"<<"y2: "<<y2<<"\n\n";
	cout<<"Triangle corner point 3: \n"<<"x3: "<<x3<<"\n"<<"y3: "<<y3<<"\n\n";
}

// ************ MAIN PROGRAM **************
int main() 
{
	char choice;
	double h, k, r, p1x, p1y, p2x, p2y, p3x, p3y;
	Line line1, line2, line3;			// lines form the triangle

	/* *** TEST INPUTS *** */
	Circle testCircle(3, 4, 5);			// h=3 k=4 r=5

	cout<<"Test Circle: (3, 4) with radius 5"<<endl<<endl;
	cout<<"Circle's equation is: \npow((x-3),2) + pow((y-4), 2) = pow(5, 2)"<<endl;
	cout<<"------------------------------------------------------------"<<endl;

	cout<<"\nTest point #1: \nx=0, y=0"<<endl;

	if( testCircle.onCircle(0, 0) ) {
		cout<<"Point 1 is on the circle"<<endl;
		line1 = testCircle.getTangent(0, 0);
	}

	cout<<"\nTest point #2: \nx=3, y=-1"<<endl;

	if( testCircle.onCircle(3, -1) ) {
		cout<<"Point 2 is on the circle"<<endl;
		line2 = testCircle.getTangent(3, -1);
	}

	cout<<"\nTest point #3: \nx=-2, y=4"<<endl;

	if( testCircle.onCircle(-2, 4) ) {
		cout<<"Point 3 is on the circle"<<"\n"<<endl;
		line3 = testCircle.getTangent(-2, 4);
	}
	cout<<"------------------------------------------------------------"<<endl;

	if( !( ( line1.getM() == line2.getM() ) || ( line2.getM() == line3.getM() ) || ( line1.getM() == line3.getM() ) ) ) {
		cout<<"\nNo parallel lines\n\n";
		Triangle testTriangle(line1, line2, line3);
		testTriangle.getCorners();
	}
	/* *** END OF TEST INPUTS *** */


	cout<<"------------------------------------------------------------"<<endl;
	cout<<"Do you want to form a new triangle?\n(y/n)";
	cin>>choice;

	/* *** USER DEFINES THE INPUTS *** */
	if(choice == 'y') {
		cout<<"\n";
		cout<<"x coordinate (center of circle): ";
		cin>>h;
		cout<<"y coordinate (center of circle): ";
		cin>>k;
		cout<<"radius of circle: ";
		cin>>r;
		
		if(r<=0) {
			cout<<"\nRadius can not be equal to or less than zero\n";
			return 1;
		}
		Circle givenCircle(h, k, r);

		cout<<"\n";
		cout<<"point 1, x coordinate: ";
		cin>>p1x;
		cout<<"point 1, y coordinate: ";
		cin>>p1y;

		if( !givenCircle.onCircle(p1x, p1y) ) {
			cout<<"\nPoint 1 is not on the circle\n";	// given point is not on the circle
			return 1;
		} 
		else
			line1 = givenCircle.getTangent(p1x, p1y);	// p1 is on circle and tangent line at that point is formed

		cout<<"point 2, x coordinate: ";
		cin>>p2x;
		cout<<"point 2, y coordinate: ";
		cin>>p2y;

		if( !givenCircle.onCircle(p2x, p2y) ) {
			cout<<"\nPoint 2 is not on the circle\n";	// given point is not on the circle
			return 1;
		}
		else
			line2 = givenCircle.getTangent(p2x, p2y);	// p2 is on circle and tangent line at that point is formed
		
		cout<<"point 3, x coordinate: ";
		cin>>p3x;
		cout<<"point 3, y coordinate: ";
		cin>>p3y;

		if( !givenCircle.onCircle(p3x, p3y) ) {
			cout<<"\nPoint 3 is not on the circle\n";	// given point is not on the circle
			return 1;
		}
		else
			line3 = givenCircle.getTangent(p3x, p3y);	// p3 is on circle and tangent line at that point is formed

		if( !( ( line1.getM() == line2.getM() ) || ( line2.getM() == line3.getM() ) || ( line1.getM() == line3.getM() ) ) ) {
			cout<<"\nNo parallel lines\n\n";
			Triangle givenTriangle(line1, line2, line3);	// everything is correct, triangle will be formed
			givenTriangle.getCorners();
		}
		else {
			cout<<"\nYou have entered parallel lines\n";	// if there are parallel lines, triangle can not be formed
			cout<<"A triangle can not be formed\n\n";
		}

	} // end of choice if

	return 0;
}