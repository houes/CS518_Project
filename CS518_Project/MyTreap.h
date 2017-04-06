#pragma once
#include "Treap.h"
#include "Edge.h"

typedef Treap<double, Edge*> Treap_;
typedef Treap_::Node EdgeNode;

class MyTreap : public Treap_
{
	public:

	EdgeNode* find_FirstEdgeNode_LeftOf(Vertex* v);

	Edge* find_FirstEdge_LeftOf(Vertex* v);

	bool empty()
	{ 
		if (root == nullptr)
			return true;
		else
			return false;
	}
};

//typedef MyTreap::Node EdgeNode;