#pragma once
#include "Triangulation.h"
#include <queue>
#include <string>

using namespace std;

void Triangulation::makeMonotone(DCEL& P)
{
	// input  P: a simple polygon stored in a DCEL
	// output P: the input simple polygon is divided into monotone polygons, stored in the same DCEL

	polygon = &P; // save as member

	priority_queue<VertexT, vector<VertexT>, LessThanByYcoord> Q;

	list<Vertex>::const_iterator it;
	for (it = P.get_vertices()->begin(); it != P.get_vertices()->end();it++)
		Q.push(VertexT(*it));

	/* initialize random seed: */
	srand(time(NULL)); // for treap insertion in handleVertex()

	while (!Q.empty())
	{
		VertexT v = Q.top();
		Q.pop();
		handleVertex(v);
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

Edge* VertexT::getPrev_ccw()
{
	// get the next edge in counter-clockwise
	// prev->v->next

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

Edge* VertexT::getNext_ccw()
{
	// get the next edge in counter-clockwise
	// prev->v->next

	Edge *prev=nullptr, *next = nullptr;

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



VertexType VertexT::determineVertexType()
{
	VertexType result;

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
			result = VertexType::SPLIT;
		else // make left turn
			result = VertexType::START;
	}
	else if (goes_DownUp(e1, e2)) // neighbour are above vertex
	{
		double crossp = e1->getVector().cross_product(e2->getVector());
		if (crossp < 0) // make right turn
			result = VertexType::MERGE;
		else // make left turn
			result = VertexType::END;
	}
	else 
		result = VertexType::REGULAR;

	setType(result);

	return result;
}

void Triangulation::handleVertex(VertexT v)
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
	switch (type)
	{
		case VertexType::START:
			handleStartVertex(v);
			break;
		case VertexType::SPLIT:
			//handleSplitVertex(v);
			break;
		case VertexType::MERGE:
			//handleMergeVertex(v);
			break;
		case VertexType::END:
			//handleEndVertex(v);
			break;
		case VertexType::REGULAR:
			//handleRegularVertex(v);
			break;
		default:
			throw invalid_argument("invalid vertex type");
	}
	
}

void Triangulation::handleStartVertex(VertexT v)
{
	Edge* ei = v.getNext_ccw();
	EdgeNode* eNode = new EdgeNode(ei->get_destination()->getX(), ei);

	// keep track of nodes created
	edgeNodeList.push_back(eNode);

	T.insert(eNode);
	helper[ei] = &v;

}

void Triangulation::handleEndVertex(VertexT v)
{
	Edge* ei_1 = v.getPrev_ccw();

	if (helper[ei_1]->getType() == VertexType::MERGE)
		polygon->split_face(ei_1, helper[ei_1]);

	T.remove(getEdgeNodeContainsEdge(ei_1));
		
}

void Triangulation::handleSplitVertex(VertexT v)
{
	Edge* ej = T.find_FirstEdge_LeftOf(&v);
	Edge* ei_1 = v.getPrev_ccw();
	Edge* ei = v.getNext_ccw();

	polygon->split_face(ei_1, helper[ej]);
	helper[ej] = &v;
	T.insert(getEdgeNodeContainsEdge(ei));
	helper[ei] = &v;

}

void Triangulation::handleMergeVertex(VertexT v)
{

}

void Triangulation::handleRegularVertex(VertexT v)
{

}

EdgeNode* Triangulation::getEdgeNodeContainsEdge(Edge* e)
{
	list<EdgeNode*>::iterator it = edgeNodeList.begin();

	while (it != edgeNodeList.end())
	{
		if((*it)->getValue()==e)
			return *it;
	}

	try{
		throw invalid_argument("No EdgeNode contains this edge!");
	}
	catch (exception& e)
	{
		cout << "exception: " << e.what() << endl << endl;
	}


	return nullptr;

}
