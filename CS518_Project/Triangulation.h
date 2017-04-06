#pragma once
#include <map>
#include "DCEL.h"
#include "MyTreap.h"


enum VertexType{REGULAR, START,SPLIT,END,MERGE,UNDEFINED};

class VertexT: public Vertex
{
	friend class Triangulation;

	VertexType type;
public:
	VertexT(Vertex v){
		x = v.getX();
		y = v.getY();
		setIncidentEdge(v.get_incidentEdge());
		type = VertexType::UNDEFINED;
	}

	void setType(VertexType type_){ type = type; }
	VertexType getType(){ return type; }

	//VertexType determineVertexType();

	//Edge* getPrev_ccw();
	//Edge* getNext_ccw();
};

class Triangulation
{
	DCEL *polygon;

	map<Edge*, Vertex*> helper;
	map<Vertex*, VertexType> vertexTypeMap;
	map<Vertex*, bool> isOnLeftChainMap;

	MyTreap T;		// edge Status

	list<EdgeNode*> edgeNodeList;

public:

	void makeMonotone(DCEL& simpleP);
	void triangulate_MonotonePolygon(DCEL& P, int nFace = 1, Face* ptr = nullptr);
	void triangulate_simple_Polygon(DCEL& simpleP);


	void handleVertex(Vertex* v);
	void handleStartVertex(Vertex* v);
	void handleEndVertex(Vertex* v);
	void handleSplitVertex(Vertex* v);
	void handleMergeVertex(Vertex* v);
	void handleRegularVertex(Vertex* v);

	VertexType determineVertexType(Vertex* v);
	EdgeNode* getEdgeNodeContainsEdge(Edge* e);

	bool isMergeVertex(Vertex* v);
	
	// for triangulate_MonotonePolygon()
	bool isVerticesOnSameChain(Vertex* v1, Vertex* v2);

	void clear();
};

struct LessThanByYcoord
{
	bool operator()(const Vertex* lhs, const Vertex* rhs) const
	{
		if (lhs->getY() < rhs->getY())
			return true;
		else if (lhs->getY() == rhs->getY())
			return lhs->getX() > rhs->getX();
		else /* lhs.getY() > rhs.getY() */
			return false;
	}
};