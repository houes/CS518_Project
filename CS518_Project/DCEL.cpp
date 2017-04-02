#include"DCEL.h"
#include <stdexcept>


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

void DCEL::split_face(Edge* h, Vertex* v)
{
	// create the edge connecting v and h.destination
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

	f1->setOuterComponent(h1);
	if (h->isOnOuterComponent()) // distinguish between cases (a) and (b)
		f2->setOuterComponent(h2);
	else
		f2->addInnerComponent(h2);
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

void DCEL::print()
{
	cout << "The faces are" << endl;
	list<Face>::iterator it = faces.begin();
	int idx = 0;
	while (it != faces.end())
	{
		cout <<"Face #"<< idx++ << endl;
		it->print();
		cout << endl;
		++it;
	}

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