
//Source: http://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/

// A C++ program to check if two given line segments intersect
#pragma once
#include "LineSegment.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(Point2D p, Point2D q, Point2D r)
{
	if (q.getX() <= max(p.getX(), r.getX()) && q.getX() >= min(p.getX(), r.getX()) &&
		q.getY() <= max(p.getY(), r.getY()) && q.getY() >= min(p.getY(), r.getY()))
		return true;

	return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point2D p, Point2D q, Point2D r)
{
	// See http://www.geeksforgeeks.org/orientation-3-ordered-points/
	// for details of below formula.

	double TOL = 1e-7;

	double val = (q.getY() - p.getY()) * (r.getX() - q.getX()) -
		(q.getX() - p.getX()) * (r.getY() - q.getY());

	if (abs(val) < TOL) return 0;  // colinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect_p(Point2D p1, Point2D q1, Point2D p2, Point2D q2)
{
	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and p2 are colinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}

bool LineSegment::doIntersect(const LineSegment& other)
{
	return doIntersect_p(p, q, other.getp(), other.getq());
}

bool LineSegment::doIntersect(const vector<LineSegment>& segs, int begin, int end)
{
	if (begin<0 || begin>segs.size() - 1 || end < begin || end>segs.size())
		throw invalid_argument("doIntersect range error");

	for (int i = begin; i < end; i++)
	{
		if (this->doIntersect(segs.at(i)))
		{
			return true;
		}

	}

	return false;
}