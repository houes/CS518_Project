#pragma once
#include <iostream>
#include "Vector.h"

using namespace std;

class Point2D
{
protected:
	double x;
	double y;

public:
	// constructer
	Point2D() { x = 0; y = 0; }
	Point2D(double x_, double y_) { x = x_; y = y_; }

	// setters
	void setX(double x_) { x= x_; }
	void setY(double y_) { y= y_; }

	// getters
	double getX() const { return x; }
	double getY() const { return y; }

	//operator
	Point2D operator*(double n)  { return Point2D(x*n, y*n); }
	Point2D operator+(Point2D p) { return Point2D(x+p.x , y+p.y);	}
	Point2D operator-(Point2D p) { return Point2D(x-p.x, y-p.y); }
	Point2D operator+(const Vector& v){ return Point2D(x + v.getX(), y + v.getY()); }

	void   scaleX(double s) { x = x/s; }
	void   scaleY(double s) { y = y/s; }


	void print() const { cout << "(" << x << "," << y << ")" << endl; }
};