#pragma once
#include <iostream>
#include <list>
#include "Edge.h"
#include "Vertex.h"
#include "Face.h"

using namespace std;

class DCEL
{
	list<Vertex>	vertices;
	list<Face>		faces;
	list<Edge>		edges;

public:
	DCEL(){}
	DCEL(const list<Vertex>& vertices_, const list<Face>& faces_, const list<Edge>& edges_){
	
		vertices = list<Vertex>(vertices_);
		faces	 = list<Face>(faces_);
		edges	 = list<Edge>(edges_);
	}

	const list<Vertex>*		get_vertices()	const	{ return &vertices; }
	const list<Face>*		get_faces()		const	{ return &faces; }
	const list<Edge>*		get_edges()		const	{ return &edges; }

	void create_an_edge(Vertex v1, Vertex v2);

	void add_vertex_at(const Vertex& v, Edge* e); // add an vertex connecting v and e.destination

	void add_vertex_at(const Vertex& v);

	void split_face(Edge* e, Vertex* v); // split the face by connecting two vertices e.destination and v. both vertices needs to be incident to the same face

	void add_edge(const Edge& e);

	void print();

	Edge* get_an_edge_at(int pos);// get a pointer to an edge in the list at pos

	// TODO:
	// DCEL* get_copy();

};