#pragma once
#include "DCEL.h"

enum VertexType{REGULAR, START,SPLIT,END,MERGE};

class VertexT: public Vertex
{
	friend class Triangulation;

	VertexType type;
public:
	VertexT(Vertex v){
		x = v.getX();
		y = v.getY();
		setIncidentEdge(v.get_incidentEdge());
	}

	void setType(VertexType type_){ type = type; }

	VertexType determineVertexType();
};

class Triangulation
{

public:
	void makeMonotone(DCEL& simpleP);

	void triangulateMonotonePolygon(DCEL& P, int nFace);

	void HandleVertex(VertexT v);
};

struct LessThanByYcoord
{
	bool operator()(const VertexT& lhs, const VertexT& rhs) const
	{
		if (lhs.getY() < rhs.getY())
			return true;
		else if (lhs.getY() == rhs.getY())
			return lhs.getX() > rhs.getX();
		else /* lhs.getY() > rhs.getY() */
			return false;
	}
};