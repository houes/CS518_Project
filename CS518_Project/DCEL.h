/**
CS518, DCEL.h
Purpose: Implementation of DCEL structure

@author Guangyu Hou
@version 0.0 04/06/17
*/

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
	
	// add a vertex connecting v and e.destination
	void	add_vertex_at(const Vertex& v, Edge* e); 

	// add an edge connecting two vertices
	void	split_face(Vertex* v1, Vertex* v2);

	// this construct a simple polygon from a set of vertices
	bool	construct_SimplePolygon(const vector<Vertex>& list);


	Edge*	get_an_edge_at(int pos);   // get a pointer to an edge   in the list at pos
	Vertex* get_an_vertex_at(int pos); // get a pointer to an vertex in the list at pos
	void	create_an_edge(Vertex v1, Vertex v2);
	void	add_vertex_at(const Vertex& v);
	void	split_face(Edge* e, Vertex* v, bool polygon_ccw = false); // split the face by connecting two vertices e.destination and v. both vertices needs to be incident to the same face
	void	add_edge(const Edge& e);

	void print();

	
	// TODO:
	// DCEL* get_copy();

	void clear()
	{
		vertices.clear();
		edges.clear();
		faces.clear();
	}

	void assignIDsAllEntities();
	Face* get_outmost_face();
};