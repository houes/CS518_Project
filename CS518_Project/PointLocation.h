/**
CS518, PointLocation.h
Purpose: Implementation Point Location class

@author Guangyu Hou
@version 0.0 04/08/17
*/

#pragma once
#include "DCEL.h"

class PointLocation
{
	DCEL* P;
public:
	PointLocation(){}
	PointLocation(DCEL* P_){ P = P_; }

	Edge* find_edge_right_below_vertex(DCEL* P, Vertex& v);

	Face* find_face_contains_vertex(DCEL* P,  Vertex& v);

	Face* find_face_contains_vertex(Edge* edge_below_vertex, Vertex& v);
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
