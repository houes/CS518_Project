#pragma once
#include "MyTreap.h"
#include "Vector.h"
#include "Vertex.h"

int compareEdgeNode_wrt_vertex(EdgeNode* e1, EdgeNode* e2, Vertex* v)
{
	// if e1, e2's relative position compare to v equals, return 0;
	// else if e1 is on the left and e2 is on the right, return 1;
	// else if e2 is on the left and e1 is on the right, return -1;

	Vector ve1 = e1->getValue()->getVector();
	Vector ve2 = e2->getValue()->getVector();

	Vector vt1 = *v - *e1->getValue()->get_destination();
	Vector vt2 = *v - *e2->getValue()->get_destination();

	double crossp1 = vt1.computeAngle_wrt(ve1);
	double crossp2 = vt2.computeAngle_wrt(ve2);

	if (crossp1*crossp2 > 0) // crossp1 and crossp2 are same sign, v is on the same side of e1,e2
	{
		if (e1->getValue()->get_destination()->getX() > e2->getValue()->get_destination()->getX())
			return 1;
		else
			return -1;
	}
	else if (crossp1 > 0 && crossp2 < 0)
		return 1;
	else // crossp1 < 0 && crossp2 > 0
		return -1;

}

bool isEdge1CloserToVertex(EdgeNode* e1, EdgeNode* e2, Vertex* v)
{
	// tell if e1's relative position w.r.t vertex v is closer compared to e2
	if (compareEdgeNode_wrt_vertex(e1, e2, v) > 0)
		return true;
	else
		return false;

}

EdgeNode* MyTreap::find_FirstEdgeNode_LeftOf(Vertex* v)
{
	EdgeNode * bestSoFar = NULL;

	// Start at the root.
	EdgeNode* node = root;

	// While subtreap rooted at node not empty...
	while (node) {
		
		Edge* e = node->getValue();
		Vertex* v2 = e->get_destination();

		Vector vec1 = e->getVector();
		Vector vec2 = *v-*v2;
		
		double crossp = vec2.computeAngle_wrt(vec1);

		if (crossp > 0) // left turn, vertex is on the right of the edge e
		{
			node = node->right;
		}
		else // right turn or vertex v is on the edge e
		{
			if ((bestSoFar == NULL) || isEdge1CloserToVertex(node, bestSoFar,v))
				bestSoFar = node;
			node = node->left;
		}

	}

	// Return.
	return bestSoFar;
}

Edge* MyTreap::find_FirstEdge_LeftOf(Vertex* v)
{
	return find_FirstEdgeNode_LeftOf(v)->getValue();
}