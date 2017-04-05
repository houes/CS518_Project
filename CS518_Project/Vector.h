#pragma once
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

class Vector
{
	double x;
	double y;

public:
	Vector(){ x = y = 0; }
	Vector(double x_, double y_) :x(x_), y(y_){}

	double getX() const { return x; }
	double getY() const { return y; }

	double length() const { return sqrt(x*x + y*y); }
	Vector operator*(double d){ return Vector(x*d, y*d); }

	double getTiltedAngle(){ 
		double result;

		if (x>=0)
			result = 180.0/M_PI*atan(y / x); 
		else
			result = 180 + 180.0 / M_PI*atan(y / x);

		if (result < 0)
			result += 360;

		return result;
	}

	void normalize(){ 
		double l = length();
		x = x / l; 
		y = y / l; 
	}

	void rotate_ccw(double angle /* in degree*/)
	{
		angle = angle / 180.0*M_PI;

		double x_ = x*cos(angle) - y*sin(angle);
		double y_ = x*sin(angle) + y*cos(angle);

		x = x_;
		y = y_;
	}

	double cross_product(const Vector& other)
	{
		return x*other.getY() - y*other.getX();
	}
};