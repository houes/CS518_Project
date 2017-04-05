#pragma once
#include "Point.h"
#include <vector>


class LineSegment
{
	Point2D p, q;
public:
	LineSegment();
	LineSegment(const Point2D& p_, const Point2D& q_) :p(p_), q(q_){}

	bool doIntersect(const LineSegment& other);
	bool doIntersect(const vector<LineSegment>& segs, int begin, int end);

	Point2D getp() const { return p; }
	Point2D getq() const { return q; }

	Vector getVector();

};
