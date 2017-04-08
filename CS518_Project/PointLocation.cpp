#pragma once
#include "PointLocation.h"
#include <algorithm>
#include <map>

bool isEdgeCrossTheSlab(Edge* e, double xStart, double xEnd)
{
	double TOL = 1e-6;

	Vertex* v1 = e->get_origin();
	Vertex* v2 = e->get_destination();

	double x_e_min = (v1->getX() < v2->getX()) ? v1->getX() : v2->getX();
	double x_e_max = (v1->getX() < v2->getX()) ? v2->getX() : v1->getX();

	if (x_e_min - xStart < TOL && xEnd - x_e_max < TOL)
		return true;
	else
		return false;
}

bool isEdgeContainedInSet(Edge* e, const vector<Edge*>& v)
{
	if (std::find(v.begin(), v.end(), e) != v.end()) {
		return true;
	}
	else {
		return false;
	}
}

double find_y_given_x_ofEdge(Edge* e,double x)
{
	Vertex* v1 = e->get_origin();
	Vertex* v2 = e->get_destination();

	Vector full;
	Vertex result;

	double dx;
	double lx = abs(v1->getX() - v2->getX());

	if (v1->getX() < v2->getX())
	{
		full = *v2 - *v1;
		dx = x - v1->getX();
		result = *v1 + full*(dx / lx);
	}
	else
	{
		full = *v1 - *v2;
		dx = x - v2->getX();
		result = *v2 + full*(dx / lx);
	}

	return result.getY();
}

bool isEdgePointingtoNegX(Edge* e)
{
	Vertex* v1 = e->get_origin();
	Vertex* v2 = e->get_destination();

	if (v1->getX() < v2->getX())
		return false;
	else
		return true;
}

Vector getVectorPointingToNegX(Edge* e)
{
	Vertex* v1 = e->get_origin();
	Vertex* v2 = e->get_destination();

	if (v1->getX() < v2->getX())
		return Vector(*v1 - *v2);
	else
		return Vector(*v2 - *v1);
}

struct EdgeLessThanByYcoord
{
	double x;

	EdgeLessThanByYcoord(double x_){ x = x_; }

	bool operator()(Edge* lhs, Edge* rhs) const
	{
		double TOL = 1e-6;

		double y1 = find_y_given_x_ofEdge(lhs, x);
		double y2 = find_y_given_x_ofEdge(rhs, x);

		Vector vec_lhs = getVectorPointingToNegX(lhs);
		Vector vec_rhs = getVectorPointingToNegX(rhs);

		double crossp = vec_rhs.cross_product(vec_lhs);


		if (y2 - y1 > TOL)
			return true;
		else if ((y1-y2)<=TOL)
		{
			if (crossp > 0)
				return true;
			else
				return false;
		}
		else
			return false;
	}
};

bool isVertexAboveEdge(Vertex *v, Edge* e)
{
	Vector vec1 = getVectorPointingToNegX(e);

	Vertex* min_x;

	if (e->get_origin()->getX() < e->get_destination()->getX())
		min_x = e->get_origin();
	else
		min_x = e->get_destination();

	Vector vec2 = *v - *min_x;

	double crossp = vec2.computeAngle_wrt(vec1);

	if (crossp > 0) // vertex below edge
		return false;
	else
		return true;

}


Edge* binarySearch(vector<Edge*> edges, Vertex* v, int left, int right) 
{
	Edge* bestSoFar = nullptr;

	if (isVertexAboveEdge(v, edges[right])) // if vertex v is above the highest edge
		return edges[right];

	while (left < right) {
		int middle = (left + right) / 2;

		if (isVertexAboveEdge(v, edges[middle]))
		{
			bestSoFar = edges[left];
			if (left == middle)
				break;
			left = middle;
		}
		else
		{
			bestSoFar = edges[right];
			if (right == middle)
				break;
			right = middle;
		}
	}

	return bestSoFar; // it will always be an edge below the vertex
}

Edge* PointLocation::find_edge_right_below_vertex(DCEL* P, Vertex& v)
{
	// find the cloest edge in P that below vertex v
	// if not found( either vertex is below lowest edge in P, 
	// or vertex is on the left or right of P), 
	// return nullptr

	vector<Vertex*> vList;
	map<int, vector<Edge*>> slab_to_edges;

	list<Vertex>::const_iterator it_v = P->get_vertices()->begin();

	while (it_v != P->get_vertices()->end())
	{
		vList.push_back(const_cast<Vertex*>(&*it_v));
		it_v++;
	}

	sort(vList.begin(), vList.end(), LessThanByXcoord());

	//for (int i = 0; i < vList.size(); i++)
	//	vList[i]->print();

	int nSlabs = vList.size() - 1;
	for (int i = 0; i < nSlabs; i++)
	{
		double xStart = vList[i]->getX();
		double xEnd = vList[i+1]->getX();

		list<Edge>::const_iterator it_e = P->get_edges()->begin();
		while (it_e != P->get_edges()->end())
		{
			Edge* e = const_cast<Edge*>(&*it_e);

			int e_ID = e->getID();

			if (isEdgeCrossTheSlab(e, xStart, xEnd) && isEdgePointingtoNegX(e))
			{
				slab_to_edges[i].push_back(e);
			}
			
			it_e++;
		}

	}

	vector<Vertex*>::iterator it_s = lower_bound(vList.begin(), vList.end(), &v, LessThanByXcoord());
	
	if (it_s == vList.begin() || it_s == vList.end()) // if v is on the left(right) of all vertices of P
		return nullptr;

	double x_after = (*it_s)->getX(); // fisrt x that is bigger than v.getX()
	double x_before = (*prev(it_s))->getX();

	// for debug
	//cout << "x_before " << x_before << " x_after " << x_after << endl;

	vector<Vertex*>::iterator it_m = vList.begin();
	int idx = -1;
	while (it_m != vList.end())
	{
		if (it_m == it_s)
			break;
		idx++;
		it_m++;
	}

	vector<Edge*> edgesInTheSlab = slab_to_edges[idx];

	double y1 = edgesInTheSlab.front()->get_origin()->getX();
	double y2 = edgesInTheSlab.front()->get_destination()->getX();

	double y_min = y1 < y2 ? y1 : y2;

	Edge lae1; //= lowest_artificial_edge1;
	Edge lae2; //= lowest_artificial_edge2;
	lae1.set_origin(&Vertex(x_after + 1, y_min - 1));
	lae2.set_origin(&Vertex(x_before - 1, y_min - 1));
	lae1.set_twin(&lae2);
	lae2.set_twin(&lae1);

	edgesInTheSlab.insert(edgesInTheSlab.begin(), &lae1);

	sort(edgesInTheSlab.begin(), edgesInTheSlab.end(), EdgeLessThanByYcoord(x_after));

	// for debug
	//for (int i = 0; i < edgesInTheSlab.size(); i++)
	//{
	//	double x1_ = edgesInTheSlab[i]->get_origin()->getX();
	//	double x2_ = edgesInTheSlab[i]->get_destination()->getX();

	//	double x1 = x1_ < x2_ ? x1_ : x2_;
	//	double x2 = x1_ > x2_ ? x1_ : x2_;

	//	cout << "Edge " << edgesInTheSlab[i]->getID()
	//		<< ": (" << x1 << ","
	//		<< x2 << ")" << endl;
	//}

	Edge* result_e = binarySearch(edgesInTheSlab, &v, 0, edgesInTheSlab.size() - 1);

	if (result_e->getID() == -1) // artificial edge found, vertex is below the lowest edge
		return nullptr;
	else
		return result_e;
}

Face* PointLocation::find_face_contains_vertex(DCEL* P, Vertex& v)
{
	Edge* e_below_v = find_edge_right_below_vertex(P, v);

	if (e_below_v != nullptr)
		return find_face_contains_vertex(e_below_v, v);
	else
		return P->get_outmost_face();
}

Face* PointLocation::find_face_contains_vertex(Edge* edge_below_vertex, Vertex& v)
{
	Edge* e1 = edge_below_vertex;
	Edge* e2 = edge_below_vertex->get_twin();

	Vector v1 = e1->getVector();
	Vector v2 = e2->getVector();

	Vector vec_v = v - *e1->get_destination();
	double crossp = vec_v.computeAngle_wrt(v1);

	if (crossp > 0) // turn left
		return e1->get_incidentFace();
	else
		return e2->get_incidentFace();
}

