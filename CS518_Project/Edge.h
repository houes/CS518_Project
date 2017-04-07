#pragma once

class Vector;
class Vertex;
class Face;

class Edge
{
	int ID;

	Vertex* Origin;
	Edge* Twin;
	Face* IncidentFace;
	Edge* Next;
	Edge* Prev;

public:
	Edge(){ ID = -1; Origin = nullptr; Twin = nullptr; IncidentFace = nullptr; Next = nullptr; Prev = nullptr; }
	Edge(Vertex* Origin_, Edge* Twin_, Face* IncidentFace_, Edge* Next_, Edge* Prev_)
	{
		Origin = Origin_;
		Twin_ = Twin;
		Next = Next_;
		Prev = Prev_;
		IncidentFace = IncidentFace_;
	}

	void setID(int ID_){ ID = ID_; }
	int  getID(){ return ID; }

	void set_origin(Vertex* v){ Origin = v; }
	void set_twin(Edge* e){ Twin = e; }
	void set_next(Edge* e){ Next = e; }
	void set_prev(Edge* e){ Prev = e; }
	void set_incidentface(Face* f){ IncidentFace = f; }

	Vertex* get_origin() const	{ return Origin; }
	Edge*	get_twin()	const	{ return Twin; }
	Edge*	get_next()	const	{ return Next; }
	Edge*	get_prev()	const	{ return Prev; }
	Face*	get_incidentFace() const { return IncidentFace; }

	Vertex* get_destination(){ return get_twin()->get_origin(); }

	bool isOnOuterComponent();
	bool isCCW(){ return isOnOuterComponent(); }

	Vector getVector();
};