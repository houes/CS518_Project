#pragma once
#include <iostream>

using namespace std;

class Point2D
{
private:
	double x;
	double y;

public:
	// constructer
	Point2D() { x = 0; y = 0; }
	Point2D(double x_, double y_) { x = x_; y = y_; }

	// getters
	double getX() { return x; }
	double getY() { return y; }

	//operator
	Point2D operator*(double n)  { return Point2D(x*n, y*n); }
	Point2D operator+(Point2D p) { return Point2D(x+p.x , y+p.y);	}
	Point2D operator-(Point2D p) { return Point2D(x-p.x, y-p.y); }
	void   scaleX(double s) { x = x/s; }
	void   scaleY(double s) { y = y/s; }

	void print() { cout << "(" << x << "," << y << ")" << endl; }
};