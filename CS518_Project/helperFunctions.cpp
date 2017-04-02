#pragma once
#include "helperFunctions.h"
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>



// helper function
bool smallerX(Point2D p1, Point2D p2)
{
	return p1.getX() < p2.getX();
}

bool smallerY(Point2D p1, Point2D p2)
{
	return p1.getY() < p2.getY();
}

// helper function
// get the boundary box of the contol points polygon
// return the left-bottum and right-top corner of the boundary box
vector<Point2D> getBoundaryBox(vector<Point2D> ctrl_pts)
{
	vector<Point2D> pts = ctrl_pts;

	double min_X, min_Y, max_X, max_Y;

	sort(pts.begin(), pts.end(), smallerX);
	min_X = pts.front().getX();
	max_X = pts.back().getX();

	sort(pts.begin(), pts.end(), smallerY);
	min_Y = pts.front().getY();
	max_Y = pts.back().getY();

	Point2D pMin(min_X, min_Y);
	Point2D pMax(max_X, max_Y);

	vector<Point2D> vec;
	vec.push_back(pMin);
	vec.push_back(pMax);
	return vec;
}

void scalePointSet(const vector<Point2D>& ctrl_pts, vector<Point2D> &pts)
{
	vector<Point2D> boundarybox = getBoundaryBox(ctrl_pts);
	Point2D pMin = boundarybox[0];
	Point2D pMax = boundarybox[1];

	double length = pMax.getX() - pMin.getX();
	double height = pMax.getY() - pMin.getY();

	double scale = length > height ? length : height;

	// transalte and scale the drawing to originate at the local [0,0]
	// with a size of (length, height) = (1, H/L) or (L/H, 1)
	for (int i = 0; i < pts.size(); i++)
	{
		pts[i] = pts[i] - pMin;
		pts[i].scaleX(scale);
		pts[i].scaleY(scale);
	}

	// scale the drawing by a factor of 0.8 and then 
	// transalte the drawing to the center of the view
	double xTranslate, yTranslate;
	if (length > height)
	{
		xTranslate = 0.1;
		yTranslate = (1 - height / length*0.8) / 2.0;
	}
	else
	{
		xTranslate = (1 - 0.8*length / height) / 2.0;
		yTranslate = 0.1;
	}
	for (int i = 0; i < pts.size(); i++)
	{
		pts[i].scaleX(1/0.8);
		pts[i].scaleY(1/0.8);
		pts[i] = pts[i] + Point2D(xTranslate, yTranslate);
	}
}

vector<Point2D> get_scaled_pts_set(const vector<Point2D>& input)
{
	vector<Point2D> output(input);

	scalePointSet(input, output);

	return output;
}

void generate_an_arrow_head(double beta, double length, Point2D ps, Point2D pt, Point2D& p1, Point2D& p2)
{
	// input:
	// bepta: half of the opening angle of the arrow head, in degree
	// length: the length of the arrow head
	// output:
	// the 2 points of the arrrow head: p2,p3 (originate from ps)

	Vector v(ps.getX() - pt.getX(), ps.getY() - pt.getY());
	v.normalize();
	v = v*length;
	Vector v1, v2;
	v1 = v2 = v;

	v1.rotate_ccw(beta);
	v2.rotate_ccw(-1*beta);

	p1 = pt + v1;
	p2 = pt + v2;
}