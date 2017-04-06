#pragma once
#include "Triangulation.h"
#include <queue>
#include <string>
#include <stack>

using namespace std;

void Triangulation::makeMonotone(DCEL& P)
{
	// input  P: a simple polygon stored in a DCEL
	// output P: the input simple polygon is divided into monotone polygons, stored in the same DCEL

	polygon = &P; // save as member

	priority_queue<Vertex*, vector<Vertex*>, LessThanByYcoord> Q;

	list<Vertex>::const_iterator it;
	for (it = P.get_vertices()->begin(); it != P.get_vertices()->end();it++)
		Q.push(const_cast<Vertex*>(&*it));

	/* initialize random seed: */
	srand(time(NULL)); // for treap insertion in handleVertex()

	while (!Q.empty())
	{
		Vertex* v = Q.top();
		Q.pop();
		handleVertex(v);
	}

	cout << endl;
}

void Triangulation::handleVertex(Vertex* v)
{
	map<VertexType, string> EnumMap;
	EnumMap[VertexType::REGULAR] = "REGULAR";
	EnumMap[VertexType::SPLIT] = "SPLIT";
	EnumMap[VertexType::START] = "START";
	EnumMap[VertexType::MERGE] = "MERGE";
	EnumMap[VertexType::END] = "END";

	VertexType type = determineVertexType(v);
	vertexTypeMap[v] = type;

	v->print(false); 
	cout << EnumMap[type] << endl;

	switch (type)
	{
		case VertexType::START:
			handleStartVertex(v);
			break;
		case VertexType::SPLIT:
			handleSplitVertex(v);
			break;
		case VertexType::MERGE:
			handleMergeVertex(v);
			break;
		case VertexType::END:
			handleEndVertex(v);
			break;
		case VertexType::REGULAR:
			handleRegularVertex(v);
			break;
		default:
			throw invalid_argument("invalid vertex type");
	}
	
}

void Triangulation::handleStartVertex(Vertex* v)
{
	Edge* ei = v->getNext_ccw();
	EdgeNode* eNode = new EdgeNode(ei->get_destination()->getX(), ei);

	// keep track of nodes created
	edgeNodeList.push_back(eNode);

	T.insert(eNode);
	helper[ei] = v;

}

void Triangulation::handleEndVertex(Vertex* v)
{
	Edge* ei_1 = v->getPrev_ccw();

	if (isMergeVertex(helper[ei_1]))
		polygon->split_face(ei_1, helper[ei_1]);

	T.remove(getEdgeNodeContainsEdge(ei_1));
		
}

void Triangulation::handleSplitVertex(Vertex* v)
{
	Edge* ej = T.find_FirstEdge_LeftOf(v);
	Edge* ei_1 = v->getPrev_ccw();
	Edge* ei = v->getNext_ccw();

	polygon->split_face(ei_1, helper[ej]);
	helper[ej] = v;
	EdgeNode* eNode = new EdgeNode(ei->get_destination()->getX(), ei);
	edgeNodeList.push_back(eNode);

	T.insert(eNode);
	helper[ei] = v;

}

void Triangulation::handleMergeVertex(Vertex* v)
{
	Edge* ei_1	= v->getPrev_ccw();
	Edge* ei	= v->getNext_ccw();

	if (isMergeVertex(helper[ei_1]))
		polygon->split_face(ei_1, helper[ei_1]);
	T.remove(getEdgeNodeContainsEdge(ei_1));

	Edge* ej = T.find_FirstEdge_LeftOf(v);
	if (isMergeVertex( helper[ej]))
		polygon->split_face(ei_1, helper[ej]);
	helper[ej] = v;
}

void Triangulation::handleRegularVertex(Vertex* v)
{
	Edge* ei_1	= v->getPrev_ccw();
	Edge* ei	= v->getNext_ccw();

	if (ei_1->get_origin()->getY() > ei_1->get_destination()->getY())// interior of P lies to the right of v
	{
		if (isMergeVertex( helper[ei_1]))
			polygon->split_face(ei_1, helper[ei_1]);

		T.remove(getEdgeNodeContainsEdge(ei_1));

		EdgeNode *eNode = new EdgeNode(ei->get_destination()->getX(), ei);
		edgeNodeList.push_back(eNode);
		T.insert(eNode);
		helper[ei] = v;
	}
	else
	{
		if (T.empty())
			throw invalid_argument("degenerated case not handled yet");

		Edge* ej = T.find_FirstEdge_LeftOf(v);
		if (isMergeVertex( helper[ej]))
			polygon->split_face(ei_1, helper[ej]);
		
		helper[ej] = v;
	}

}

bool Triangulation::isMergeVertex(Vertex* v)
{
	if (vertexTypeMap[v] == VertexType::MERGE)
		return true;
	else
		return false;
}

EdgeNode* Triangulation::getEdgeNodeContainsEdge(Edge* e)
{
	list<EdgeNode*>::iterator it = edgeNodeList.begin();

	while (it != edgeNodeList.end())
	{
		if ((*it)->getValue() == e)
			return *it;
		else
			it++;
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

VertexType Triangulation::determineVertexType(Vertex* v)
{
	VertexType result;

	// in CCW order, e1->vertex->e2
	Edge *e1 = v->getPrev_ccw();
	Edge *e2 = v->getNext_ccw();

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

void Triangulation::triangulate_MonotonePolygon(DCEL& P, int nFace)
{
	if (nFace<0 || nFace>P.get_faces()->size()-1)
		throw invalid_argument(" face number out of range");

	vector<Vertex*> vList;
	list<Face>::const_iterator it_f = P.get_faces()->begin();
	
	int iFace = 0;
	while (iFace++ < nFace)
		it_f++;

	Edge* e0 = it_f->get_outerComponent();
	Edge* ei = e0;

	do
	{
		vList.push_back(ei->get_destination());
		ei = ei->get_next();

	} while (ei != e0);

	//list<Vertex>::const_iterator it = P.get_vertices()->begin();

	//for (; it != P.get_vertices()->end(); it++)
	//	vList.push_back(const_cast<Vertex*>(&*it));

	sort(vList.rbegin(), vList.rend(), LessThanByYcoord()); // sorted in reverse order

	for (int i = 0; i < vList.size(); i++)
		vList[i]->print();

	Vertex* topmost = vList.front();
	Vertex* lowest = vList.back();

	Edge* leftChain0 = topmost->getNext_ccw();
	Edge* rightChain0 = lowest->getNext_ccw();

	Edge* left_e = leftChain0, *right_e = rightChain0;
	
	cout << endl;
	while (left_e->get_destination() != lowest)
	{
		left_e->get_destination()->print(); // debug

		isOnLeftChainMap[left_e->get_destination()] = true;
		left_e = left_e->get_next();
	}

	while (right_e->get_destination() != topmost)
	{
		right_e->get_destination()->print(); // debug

		isOnLeftChainMap[right_e->get_destination()] = false;
		right_e = right_e->get_next();
	}

	stack<Vertex*> S;

	S.push(vList.front());  // u1
	S.push(vList.at(1));	// u2

	for (int j = 2; j < vList.size()-1; j++)
	{
		Vertex* vj = vList[j];
		Vertex* vj_1 = S.top();

		if (!isVerticesOnSameChain(vj, S.top()))
		{
			while (S.size()>1)
			{
				Vertex* v = S.top();

				Face* vj_f = vj->get_incidentEdge()->get_incidentFace();

				P.split_face(v->getPrev_ccw(vj_f), vj);
				S.pop();
			}
			S.pop();

			S.push(vj_1);
			S.push(vj);
		}
		else
		{
			S.pop();

			Vertex* x	= vj_1;
			Vertex* vk = S.top();

			Vector vec1 = *x - *vj;
			Vector vec2 = *vk - *x;

			double crossp = vec2.computeAngle_wrt(vec1);

			int vjOnleftChain = -1;

			if (isOnLeftChainMap[vj])
				vjOnleftChain = 1;
			else
				vjOnleftChain = -1;

			// requires that
			// left turn if vj is on right chain, right turn if vj is on left chain
			while ( crossp * vjOnleftChain < 0) 
			{
				Face* vj_f = vj->get_incidentEdge()->get_incidentFace();

				if (vjOnleftChain<0)
					P.split_face(x->getNext_ccw(vj_f), vj);
				else
					P.split_face(vk->getPrev_ccw(vj_f), vj);

				x = vk;

				S.pop();
				if (S.empty())
					break;

				vk = S.top();

				vec1 = *x - *vj;
				vec2 = *vk - *x;
			}

			S.push(x);
			S.push(vj);
		}
	}

	Vertex* vn = lowest;

	if(!S.empty())
		S.pop();

	while (S.size()>1)
	{
		Vertex* v = S.top();
		P.split_face(v->getPrev_ccw(), vn);
		S.pop();
	}
}

bool Triangulation::isVerticesOnSameChain(Vertex* v1, Vertex* v2)
{
	if (isOnLeftChainMap[v1] == isOnLeftChainMap[v2])
		return true;
	else
		return false;
}