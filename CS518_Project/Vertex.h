#pragma once
#include <iostream>
#include "Point.h"

using namespace std;

class Edge;

class Vertex : public Point2D
{
	Edge *IncidentEdge;

public:
	Vertex();
	Vertex(double x_, double y_);
	Vertex(double x_, double y_, Edge* IncidentEdge_);

	void setIncidentEdge(Edge* e){ IncidentEdge = e; }
	Edge* get_incidentEdge(){ return IncidentEdge; }

	bool operator==(const Vertex& other)
	{
		if (this->getX() == other.getX() && this->getY() == other.getY())
			return true;
		else
			return false;
	}
};