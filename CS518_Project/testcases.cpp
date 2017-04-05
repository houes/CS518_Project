#pragma once
#include <vector>
#include "DCEL.h"
#include "Triangulation.h"
#include "helperFunctions.h"


extern DCEL	data;

void runTestCases(int caseID)
{

	vector<Vertex> list_book = { Vertex(1117,-411), Vertex(1037,-383), Vertex(1030,-179),
		Vertex(934, -227), Vertex(875, -188), Vertex(769, -244), Vertex(835, -327), 
		Vertex(813, -419), Vertex(737,-362), Vertex(709,-536), Vertex(795,-649), 
		Vertex(890, -594), Vertex(991, -651), Vertex(968, -491), Vertex(1109,-535) };

	//for (int i = 0; i < list_book.size(); i++)
	//{
	//	Point2D p = list_book[i]* 0.001;
	//	list_book[i].setX(p.getX());
	//	list_book[i].setY(p.getY());
	//}

	vector<Vertex> reference(list_book);
	scalePointSet(reference, list_book);

	vector<Vertex> list = { Vertex(0.1, 0.1), Vertex(0.15, 0.7), Vertex(0.3, 0.8), 
		Vertex(0.6, 0.7), Vertex(0.7, 0.5), Vertex(0.5, 0.6), Vertex(0.2, 0.4) };

	data.construct_SimplePolygon(list);

	Triangulation tri;
	tri.makeMonotone(data);

	//// case 1:
	//data.create_an_edge(Vertex(0.1, 0.1), Vertex(0.15, 0.7));

	//data.add_vertex_at(Vertex(0.3, 0.8));
	//data.add_vertex_at(Vertex(0.6, 0.7));
	//data.add_vertex_at(Vertex(0.7, 0.5));
	//data.add_vertex_at(Vertex(0.5, 0.6));
	//data.add_vertex_at(Vertex(0.2, 0.4));
	////data.add_vertex_at(Vertex(0.4, 0.3));
	////data.add_vertex_at(Vertex(0.3, 0.2));

	//data.split_face(data.get_an_edge_at(1), const_cast<Vertex*>(&data.get_vertices()->back()));

	//data.split_face(data.get_an_edge_at(5), data.get_an_vertex_at(5));

	//data.add_vertex_at(Vertex(0.4, 0.2), data.get_an_edge_at(10));

	//data.add_vertex_at(Vertex(0.9,0.9), data.get_an_edge_at(4));

	//data.split_face(data.get_an_edge_at(15), data.get_an_vertex_at(6));

	//data.split_face(data.get_an_edge_at(14), data.get_an_vertex_at(3));

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