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


Edge* Vertex::getPrev_ccw(Face* f)
{
	// get the next edge in counter-clockwise
	// prev->v->next
	// if Face f is provided, then the incident face of this edge should match f

	if (f != nullptr)
	{
		vector<Edge*> inciBackEdges = getIncidentBackEdges();
		for (int i = 0; i < inciBackEdges.size(); i++)
		{
			if (inciBackEdges[i]->get_incidentFace() == f)
				return inciBackEdges[i];
		}
		
		throw invalid_argument("the specified face can not be found for any incident edge of this vertex");
	}

	Edge *prev = nullptr, *next = nullptr;

	if (get_incidentEdge()->isCCW())
	{
		next = get_incidentEdge();
		prev = next->get_prev();
	}
	else
	{
		prev = get_incidentEdge()->get_twin();
		next = prev->get_next();
	}

	return prev;
}

Edge* Vertex::getNext_ccw(Face* f)
{
	// get the next edge in counter-clockwise
	// prev->v->next
	// if Face f is provided, then the incident face of this edge should match f

	if (f != nullptr)
	{
		vector<Edge*> inciEdges = getIncidentEdges();
		for (int i = 0; i < inciEdges.size(); i++)
		{
			if (inciEdges[i]->get_incidentFace() == f)
				return inciEdges[i];
		}

		throw invalid_argument("the specified face can not be found for any incident edge of this vertex");
	}

	Edge *prev = nullptr, *next = nullptr;

	if (get_incidentEdge()->isCCW())
	{
		next = get_incidentEdge();
		prev = next->get_prev();
	}
	else
	{
		prev = get_incidentEdge()->get_twin();
		next = prev->get_next();
	}

	return next;
}

vector<Edge*> Vertex::getIncidentEdges()
{
	Edge *prev = nullptr, *next = nullptr;

	if (get_incidentEdge()->isCCW())
	{
		next = get_incidentEdge();
		prev = next->get_prev();
	}
	else
	{
		prev = get_incidentEdge()->get_twin();
		next = prev->get_next();
	}

	vector<Edge*> result;
	
	Edge* e = next;

	do
	{
		result.push_back(e);
		e = e->get_twin()->get_next();
	} while (e != next);

	return result;
}

vector<Edge*> Vertex::getIncidentEdges_ccw()
{
	vector<Edge*> result;

	vector<Edge*> inciEdges = getIncidentEdges();

	for (int i = 0; i < inciEdges.size(); i++)
	{
		if (inciEdges[i]->isCCW())
			result.push_back(inciEdges[i]);
	}

	return result;

}

vector<Edge*> Vertex::getIncidentBackEdges()
{
	vector<Edge*> result;

	vector<Edge*> inciEdges = getIncidentEdges();

	for (int i = 0; i < inciEdges.size(); i++)
		result.push_back(inciEdges[i]->get_twin());

	return result;
}

vector<Face*> Vertex::getIncidentFaces_ccw()
{
	// get the incident faces of a vertex, select only the faces that is ccw
	vector<Face*> result;

	vector<Edge*> edges = getIncidentEdges_ccw();

	for (int i = 0; i < edges.size(); i++)
		result.push_back(edges[i]->get_incidentFace());

	return result;
}