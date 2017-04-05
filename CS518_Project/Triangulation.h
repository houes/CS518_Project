#pragma once
#include <map>
#include "DCEL.h"
#include "MyTreap.h"


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
	VertexType getType(){ return type; }

	VertexType determineVertexType();

	Edge* getPrev_ccw();
	Edge* getNext_ccw();
};

class Triangulation
{
	DCEL *polygon;

	map<Edge*, VertexT*> helper;
	MyTreap T;		// edge Status

	list<EdgeNode*> edgeNodeList;

public:
	//Triangulation();
	//Triangulation(DCEL* polygon_){ polygon = polygon_; }

	void makeMonotone(DCEL& simpleP);

	void triangulateMonotonePolygon(DCEL& P, int nFace);

	void handleVertex(VertexT v);

	void handleStartVertex(VertexT v);
	void handleEndVertex(VertexT v);
	void handleSplitVertex(VertexT v);
	void handleMergeVertex(VertexT v);
	void handleRegularVertex(VertexT v);

	EdgeNode* getEdgeNodeContainsEdge(Edge* e);
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