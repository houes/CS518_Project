#include "DCEL.h"

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