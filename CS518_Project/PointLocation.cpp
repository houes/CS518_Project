#pragma once
#include "PointLocation.h"
#include <algorithm>
#include <map>

bool isEdgeCrossTheSlab(Edge* e, double xStart, double xEnd)
{
	Vertex* v1 = e->get_origin();
	Vertex* v2 = e->get_destination();

	double x_e_min = (v1->getX() < v2->getX()) ? v1->getX() : v2->getX();
	double x_e_max = (v1->getX() < v2->getX()) ? v2->getX() : v1->getX();

	if (x_e_min <= xStart && x_e_max >= xEnd)
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
		double y1 = find_y_given_x_ofEdge(lhs, x);
		double y2 = find_y_given_x_ofEdge(rhs, x);

		if (y1<y2)
			return true;
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

	while (left <= right) {
		int middle = (left + right) / 2;

		if (isVertexAboveEdge(v, edges[middle]))
		{
			bestSoFar = edges[left];
			left = middle + 1;
		}
		else
		{
			bestSoFar = edges[right];
			right = middle - 1;
		}
	}

	if (isVertexAboveEdge(v, bestSoFar))
		return bestSoFar;
	else
		return bestSoFar; // needs change here
}

Edge* PointLocation::find_edge_above_vertex(DCEL* P, Vertex& v)
{
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
			if (isEdgeCrossTheSlab(e, xStart, xEnd) && !isEdgeContainedInSet(e->get_twin(), slab_to_edges[i]))
			{
				slab_to_edges[i].push_back(e);
			}
			
			it_e++;
		}

	}

	vector<Vertex*>::iterator it_s = lower_bound(vList.begin(), vList.end(), &v, LessThanByXcoord());
	double x_vertex = (*it_s)->getX(); // fisrt x that is bigger than v.getX()
	vector<Vertex*>::iterator it_m = vList.begin();
	int idx = 0;
	while (it_m != vList.end())
	{
		if (it_m == it_s)
			break;
		idx++;
		it_m++;
	}

	vector<Edge*> edgesInTheSlab = slab_to_edges[idx];

	sort(edgesInTheSlab.begin(), edgesInTheSlab.end(), EdgeLessThanByYcoord(x_vertex));

	for (int i = 0; i < edgesInTheSlab.size(); i++)
		cout << "Edge " << edgesInTheSlab[i]->getID() << endl;

	Edge* result_e = binarySearch(edgesInTheSlab, &v, 0, edgesInTheSlab.size() - 1);

	return result_e;
}

Face* PointLocation::find_polygon_contains_vertex(DCEL* P, Vertex& v)
{

	Edge* hit_e = find_edge_above_vertex(P, v);

	if (hit_e->isCCW())
		return hit_e->get_incidentFace();
	else
		return hit_e->get_twin()->get_incidentFace();
}
