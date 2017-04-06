#pragma once
#include <iostream>
#include <vector>
#include "Point.h"


class Face;

using namespace std;

class Edge;

class Vertex : public Point2D
{
	int ID;
	Edge *IncidentEdge;

public:
	Vertex();
	Vertex(double x_, double y_);
	Vertex(double x_, double y_, Edge* IncidentEdge_);

	void setID(int ID_){ ID = ID_; }

	void setIncidentEdge(Edge* e){ IncidentEdge = e; }
	Edge* get_incidentEdge(){ return IncidentEdge; }

	bool operator==(const Vertex& other)
	{
		if (this->getX() == other.getX() && this->getY() == other.getY())
			return true;
		else
			return false;
	}

	void add(Vector v) 
	{ 
		setX(x + v.getX());
		setY(y + v.getY()); 
	}

	Vector  operator-(const Vertex& other) 
	{ 
		return Vector(getX() - other.getX(), getY() - other.getY());
	}

	void print(bool newline = true);

	Edge* getPrev_ccw(Face* f = nullptr);
	Edge* getNext_ccw(Face* f = nullptr);

	vector<Edge*> getIncidentEdges();
};