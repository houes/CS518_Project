#pragma once
#include <iostream>
#include "Point.h"
#include <vector>

using namespace std;

class Vertex;
class Face;
class Edge;


class Vertex : Point2D
{
	Edge *IncidentEdge;

public:
	Vertex();
	Vertex(double x_, double y_, Edge* IncidentEdge_);

	Edge* get_incidentEdge(){ return IncidentEdge; }
};

class Face
{
	Edge *OuterComponent;
	Edge *InnerComponent;
public:
	Face(){ OuterComponent = nullptr; InnerComponent = nullptr; }
	Face(Edge *OuterComponent_, Edge *InnerComponent_)
	{ OuterComponent = OuterComponent_; InnerComponent = InnerComponent_; }

	Edge* get_outerComponent(){ return OuterComponent; }
	Edge* get_innerComponent(){ return InnerComponent; }
};

class Edge
{
	Vertex* Origin;
	Edge* Twin;
	Face* IncidentFace;
	Edge* Next;
	Edge* Prev;
public:
	Edge(){ Origin = nullptr; Twin = nullptr; IncidentFace = nullptr; Next = nullptr; Prev = nullptr; }
	Edge(Vertex* Origin_, Edge* Twin_, Face* IncidentFace_, Edge* Next_, Edge* Prev_)
	{
		Origin	= Origin_;
		Twin_	= Twin;
		Next	= Next_;
		Prev	= Prev_;
		IncidentFace = IncidentFace_;
	}

	Vertex* get_origin()	{ return Origin; }
	Edge*	get_twin()		{ return Twin; }
	Edge*	get_next()		{ return Next; }
	Edge*	get_prev()		{ return Prev; }
	Face*	get_incidentFace(){ return IncidentFace; }

	Vertex* get_destination(){ return get_twin()->get_origin(); }

};

class DCEL
{
	vector<Vertex>	vertices;
	vector<Face>	faces;
	vector<Edge>	edges;

public:
	DCEL(){}
	DCEL(const vector<Vertex>& vertices_, const vector<Face>& faces_, const vector<Edge>& edges_){
	
		vertices = vector<Vertex>(vertices_);
		faces	 = vector<Face>(faces_);
		edges	 = vector<Edge>(edges_);
	}

	void add_vertex(const Vertex& v);
	void add_edge(const Edge& e);

};