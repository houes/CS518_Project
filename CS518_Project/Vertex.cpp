#pragma once
#include "DCEL.h"
#include <iomanip>

Vertex::Vertex() :Point2D()
{
	IncidentEdge = nullptr;
}

Vertex::Vertex(double x_, double y_) :Point2D(x_, y_)
{
	IncidentEdge = nullptr;
}

Vertex::Vertex(double x_, double y_, Edge* IncidentEdge_) : Point2D(x_,y_)
{
	IncidentEdge = IncidentEdge_;
}

void Vertex::print(bool newline)
{
	cout.precision(2);

	cout << "(" << setw(3) << getX() << "," << setw(3) << getY() << ")";

	if (newline)
		cout << endl;
	else
		cout << "	";
}