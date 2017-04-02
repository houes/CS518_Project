#pragma once
#include "DCEL.h"
#include <vector>

extern DCEL	data;

void runTestCases(int caseID)
{
	// case 1:
	data.create_an_edge(Vertex(0.1, 0.1), Vertex(0.15, 0.7));

	data.add_vertex_at(Vertex(0.3, 0.8));
	data.add_vertex_at(Vertex(0.6, 0.7));
	data.add_vertex_at(Vertex(0.7, 0.5));
	data.add_vertex_at(Vertex(0.5, 0.6));
	data.add_vertex_at(Vertex(0.2, 0.4));
	//data.add_vertex_at(Vertex(0.4, 0.3));
	//data.add_vertex_at(Vertex(0.3, 0.2));

	data.split_face(data.get_an_edge_at(1), const_cast<Vertex*>(&data.get_vertices()->back()));

	data.split_face(data.get_an_edge_at(5), data.get_an_vertex_at(5));

	data.add_vertex_at(Vertex(0.4, 0.2), data.get_an_edge_at(10));

	data.add_vertex_at(Vertex(0.9,0.9), data.get_an_edge_at(4));

	data.split_face(data.get_an_edge_at(15), data.get_an_vertex_at(6));

	data.split_face(data.get_an_edge_at(14), data.get_an_vertex_at(3));

	// case 2:
	//data.create_an_edge(Vertex(0.1, 0.1), Vertex(0.15, 0.7));

	//data.add_vertex_at(Vertex(0.3, 0.8));
	//data.add_vertex_at(Vertex(0.6, 0.7));
	//data.add_vertex_at(Vertex(0.7, 0.5));
	////data.add_vertex_at(Vertex(0.5, 0.6));
	////data.add_vertex_at(Vertex(0.2, 0.4));
	////data.add_vertex_at(Vertex(0.4, 0.3));
	////data.add_vertex_at(Vertex(0.3, 0.2));

	//data.add_vertex_at(Vertex(0.6, 0.3));
	//data.add_vertex_at(Vertex(0.9, 0.8), data.get_an_edge_at(7));

	//data.split_face(data.get_an_edge_at(1), const_cast<Vertex*>(&data.get_vertices()->back()));

	// case 3:
	//data.create_an_edge(Vertex(0.1, 0.1), Vertex(0.15, 0.7));

	//data.add_vertex_at(Vertex(0.3, 0.8));
	//data.add_vertex_at(Vertex(0.6, 0.7));
	//data.add_vertex_at(Vertex(0.7, 0.5));
	////data.add_vertex_at(Vertex(0.5, 0.6));
	////data.add_vertex_at(Vertex(0.2, 0.4));
	////data.add_vertex_at(Vertex(0.4, 0.3));
	////data.add_vertex_at(Vertex(0.3, 0.2));

	//data.split_face(data.get_an_edge_at(1), const_cast<Vertex*>(&data.get_vertices()->back()));

	//data.add_vertex_at(Vertex(0.6, 0.3));
	//data.add_vertex_at(Vertex(0.9, 0.8), data.get_an_edge_at(7));


}