#pragma once
#include "Triangulation.h"
#include "Treap.h"
#include <queue>
#include <map>
#include <string>

using namespace std;

typedef Treap<double, Edge> MyTreap;
typedef MyTreap::Node MyNode;

void Triangulation::makeMonotone(DCEL& P)
{
	// input  P: a simple polygon stored in a DCEL
	// output P: the input simple polygon is divided into monotone polygons, stored in the same DCEL

	priority_queue<VertexT, vector<VertexT>, LessThanByYcoord> Q;

	list<Vertex>::const_iterator it;
	for (it = P.get_vertices()->begin(); it != P.get_vertices()->end();it++)
		Q.push(VertexT(*it));

	MyTreap T;

	while (!Q.empty())
	{
		VertexT v = Q.top();
		Q.pop();
		HandleVertex(v);
	}
}

bool goes_UpDown(Edge* e1, Edge* e2)
{
	// assume e1->e2 in ccw, there are 3 points

	double y1 = e1->get_origin()->getY();
	double y2 = e1->get_destination()->getY();
	double y3 = e2->get_destination()->getY();

	if (y2 > y1 && y2 > y3)
		return true;
	else 
		return false;
}

bool goes_DownUp(Edge* e1, Edge* e2)
{
	// assume e1->e2 in ccw, there are 3 points

	double y1 = e1->get_origin()->getY();
	double y2 = e1->get_destination()->getY();
	double y3 = e2->get_destination()->getY();

	if (y2 < y1 && y2 < y3)
		return true;
	else
		return false;
}

VertexType VertexT::determineVertexType()
{
	Edge *e1, *e2; // in CCW order, e1->vertex->e2

	if (get_incidentEdge()->isCCW())
	{
		e2 = get_incidentEdge();
		e1 = e2->get_prev();
	}
	else
	{
		e1 = get_incidentEdge()->get_twin();
		e2 = e1->get_next();
	}

	if (goes_UpDown(e1, e2)) // neighbour are below vertex
	{
		double crossp = e1->getVector().cross_product(e2->getVector());
		if (crossp < 0) // make right turn
			return VertexType::SPLIT;
		else // make left turn
			return VertexType::START;
	}
	else if (goes_DownUp(e1, e2)) // neighbour are above vertex
	{
		double crossp = e1->getVector().cross_product(e2->getVector());
		if (crossp < 0) // make right turn
			return VertexType::MERGE;
		else // make left turn
			return VertexType::END;
	}
	else 
		return VertexType::REGULAR;

		
}

void Triangulation::HandleVertex(VertexT v)
{
	map<VertexType, string> EnumMap;
	EnumMap[VertexType::REGULAR] = "REGULAR";
	EnumMap[VertexType::SPLIT] = "SPLIT";
	EnumMap[VertexType::START] = "START";
	EnumMap[VertexType::MERGE] = "MERGE";
	EnumMap[VertexType::END] = "END";

	VertexType type = v.determineVertexType();

	v.print(false); 
	cout << EnumMap[type] << endl;
	
}