#pragma once
#include "DCEL.h"

class PointLocation
{
	DCEL* P;
public:
	PointLocation(){}
	PointLocation(DCEL* P_){ P = P_; }

	Edge* find_edge_above_vertex(DCEL* P, Vertex& v);

	Face* find_polygon_contains_vertex(DCEL* P,  Vertex& v);
};

struct LessThanByXcoord
{
	bool operator()(const Vertex* lhs, const Vertex* rhs) const
	{
		if (lhs->getX() < rhs->getX())
			return true;
		else if (lhs->getX() == rhs->getX())
			return lhs->getY() < rhs->getY();
		else 
			return false;
	}
};
