#pragma once
#include"DCEL.h"
#include <stdexcept>
#include "LineSegment.h"


void DCEL::create_an_edge(Vertex v1_, Vertex v2_)
{
	if (vertices.empty() && edges.empty() && faces.empty())
		;
	else
	{
		throw invalid_argument(" The current DCEL is not empty! Aborted ");
	}
		

	vertices.push_back(v1_);
	vertices.push_back(v2_);

	edges.push_back(Edge());
	edges.push_back(Edge());

	faces.push_back(Face());

	list<Vertex>::iterator it1 = vertices.begin();
	Vertex &v1 = *it1;
	Vertex &v2 = *(++it1);

	list<Edge>::iterator it2 = edges.begin();
	Edge &e1 = *it2;
	Edge &e2 = *(++it2);

	Face& f0 = faces.front();

	v1.setIncidentEdge(&e1);
	v2.setIncidentEdge(&e2);

	f0.addInnerComponent(&e1);
	f0.setOuterComponent(nullptr);

	e1.set_origin(&v1);
	e1.set_twin(&e2);
	e1.set_incidentface(&f0);
	e1.set_next(&e2);
	e1.set_prev(&e2);

	e2.set_origin(&v2);
	e2.set_twin(&e1);
	e2.set_incidentface(&f0);
	e2.set_next(&e1);
	e2.set_prev(&e1);
}

void DCEL::add_vertex_at(const Vertex& v_, Edge* h)
{
	// add a vertex v_ which also add an edge connecting v_ and h.destination

	vertices.push_back(v_);
	Vertex* v = &vertices.back();
	edges.push_back(Edge());
	Edge* h1 = &edges.back();
	edges.push_back(Edge());
	Edge* h2 = &edges.back();

	v->setIncidentEdge(h2);
	h1->set_twin(h2);
	h2->set_twin(h1);
	h1->set_origin(h->get_destination());
	h2->set_origin(v);
	h1->set_incidentface(h->get_incidentFace());
	h2->set_incidentface(h->get_incidentFace());
	h1->set_next(h2);
	h2->set_next(h->get_next());
	h1->set_prev(h);
	h2->set_prev(h1);
	h->set_next(h1);
	h2->get_next()->set_prev(h2);
}

void DCEL::add_vertex_at(const Vertex& v)
{
	// by default, the vertex v adds to connect the last vertex added

	// find the halfedge whose destination is the last added vertex
	Edge* h = get_an_edge_at(2 * (edges.size() / 2 - 1));

	add_vertex_at(v, h);

}

void DCEL::add_edge(const Edge& e)
{
	//TODO
}

void DCEL::split_face(Edge* h, Vertex* v, bool polygon_ccw)
{
	// create the edge connecting h.destination and v
	// pre-condition: (1) the vertices v and h.destination should be in the same face
	//				  (2) the vertices v and h.destination are not adjacent
	// we consider two cases:
	//				  (a) h is on the outercomponent
	//				  (b) h is on the innercomponents
	
	Face* f0 = h->get_incidentFace();

	faces.push_back(Face());
	Face* f1 = &faces.back();
	faces.push_back(Face());
	Face* f2 = &faces.back();
	edges.push_back(Edge());
	Edge* h1 = &edges.back();
	edges.push_back(Edge());
	Edge* h2 = &edges.back();


	if (h->isOnOuterComponent()) // distinguish between cases (a) and (b)
	{
		f1->setOuterComponent(h1);
		f2->setOuterComponent(h2);
	}
	else
	{
		if (polygon_ccw)
		{
			f1->addInnerComponent(h1);
			f2->setOuterComponent(h2);
		}
		else
		{
			f1->setOuterComponent(h1);
			f2->addInnerComponent(h2);
		}
	}

	h1->set_twin(h2);
	h2->set_twin(h1);
	h1->set_origin(h->get_destination());
	h2->set_origin(v);
	h2->set_next(h->get_next());
	h2->get_next()->set_prev(h2);
	h1->set_prev(h);
	h->set_next(h1);
	Edge* i = h2;
	while (1)
	{
		i->set_incidentface(f2);
		if (i->get_destination() == v)
			break;
		i = i->get_next();
	}
	h1->set_next(i->get_next());
	h1->get_next()->set_prev(h1);
	i->set_next(h2);
	h2->set_prev(i);
	i = h1;
	while (1)
	{
		i->set_incidentface(f1);
		i = i->get_next();
		if (i->get_destination() == v)
			break;
	}

	// delete f0
	list<Face>::iterator it = faces.begin();
	while (&*it != f0)
		it++;
	faces.erase(it);

}

void DCEL::split_face(Vertex* v1, Vertex* v2)
{
	// create the edge connecting v1 and v2
	// will detect if v1 and v2 has any shared face, if so, connect, if not throw exception

	vector<Face*> v1faces = v1->getIncidentFaces_ccw();
	vector<Face*> v2faces = v2->getIncidentFaces_ccw();

	Face* sharedFace = nullptr;
	bool innerBreaked = false;

	for (int i = 0; i < v1faces.size(); i++)
	{
		for (int j = 0; j < v2faces.size(); j++)
		{
			if (v1faces[i] == v2faces[j])
			{
				sharedFace = v1faces[i];
				innerBreaked = true;
				break;
			}

		}
		if (innerBreaked)
			break;
	}

	if (sharedFace == nullptr)
		throw invalid_argument("no face is shared by this two vertices!");

	Edge* e = v1->getPrev_ccw(sharedFace);

	split_face(e, v2);
}

void DCEL::print()
{
	cout << endl;
	cout << "*** The resulting faces are *** " << endl;
	list<Face>::iterator it = faces.begin();
	int idx = 0;
	while (it != faces.end())
	{
		cout <<"Face #"<< idx++ << endl;
		it->print();
		cout << endl;
		++it;
	}
	cout << "*** End showing resulting faces *** " << endl;
}

Edge* DCEL::get_an_edge_at(int pos)
{
	if (pos<0 || pos>edges.size()-1)
		throw invalid_argument("pos out of range");

	list<Edge>::iterator it = edges.begin();

	int i = 0;
	while (i++ < pos)
	{
		if (it != edges.end())
			it++;
		else
			throw invalid_argument("pos out of range");
	}

	return &*it;
}

Vertex* DCEL::get_an_vertex_at(int pos)
{
	if (pos<0 || pos>vertices.size() - 1)
		throw invalid_argument("pos out of range");

	list<Vertex>::iterator it = vertices.begin();

	int i = 0;
	while (i++ < pos)
	{
		if (it != vertices.end())
			it++;
		else
			throw invalid_argument("pos out of range");
	}

	return &*it;
}

bool DCEL::construct_SimplePolygon(const vector<Vertex>& list)
{
	// construct a simple polygon from ordered vertices provided, 
	// if not possible, return false;

	if (list.empty() || list.size() == 1)
		throw invalid_argument("not enough vertices(<=1)");

	vector<LineSegment> segs;
	vector<Vertex>::const_iterator it = list.begin();

	segs.push_back(LineSegment(*it, *(it + 1)));
	create_an_edge(*it, *(it + 1));

	it++;
	it++;

	while (it != list.end())
	{
		LineSegment l( *(prev(it)), *(it));

		try{
			if (l.doIntersect(segs, 0, segs.size() - 1))
				throw invalid_argument("not simply polygon! abort");
		}
		catch (std::exception& e)
		{
			cout << "exception: " << e.what() << endl << endl;
			return false;
		}


		segs.push_back(l);

		add_vertex_at(*(it++));
	}

	it--;

	try{
		LineSegment l(*it, vertices.front());
		if (l.doIntersect(segs, 1, segs.size() - 1))
			throw invalid_argument("not simply polygon! abort");
		segs.push_back(l);
	}
	catch (std::exception& e)
	{
		cout << "exception: " << e.what() << endl << endl;
		return false;
	}

	// compute whether the polygon traverse ccw or cw when finally spliced(connected)
	bool polygon_ccw = false;

	double accumulated_angle = 0;
	for (int i = 0; i < segs.size(); i++)
	{
		Vector v1, v2;

		v1 = segs[i].getVector();
		v2 = segs[(i + 1) % segs.size()].getVector();

		double angle = v2.computeAngle_wrt(v1);
		accumulated_angle += angle;
	}

	if (accumulated_angle > 0)
		polygon_ccw = true; // h1 inner component
	else
		polygon_ccw = false; // h1 outer component

	split_face(get_an_edge_at(1), get_an_vertex_at(vertices.size() - 1), polygon_ccw);

	return true;

}

void DCEL::assignIDsAllEntities()
{
	// assign each face, edge and vertex a unique ID, to distinguwish them later

	list<Vertex>::iterator it1	= vertices.begin(); 
	list<Edge>::iterator it2	= edges.begin();
	list<Face>::iterator it3	= faces.begin();

	int idx = 0;
	while (it1 != vertices.end())
	{
		it1->setID(idx++);
		it1++;
	}

	idx = 0;
	while (it2 != edges.end())
	{
		it2->setID(idx++);
		it2++;
	}

	idx = 0;
	while (it3 != faces.end())
	{
		it3->setID(idx++);
		it3++;
	}
}

Face* DCEL::get_outmost_face()
{
	// for now, I assume there is only ONE face that has innercomponnet
	// which is the outmost face, if there are other faces having innercomponent,
	// needs to change this function

	list<Face>::iterator it = faces.begin();

	while (it != faces.end())
	{
		if (it->hasInnerComponent())
			break;
		it++;
	}

	return &*it;
}