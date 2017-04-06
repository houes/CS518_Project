#pragma once
#include <vector>
#include "DCEL.h"
#include "Triangulation.h"
#include "helperFunctions.h"


extern DCEL	data;

void assignIDstoVertices(vector<Vertex>& list);

void runTestCases(int caseID)
{

	vector<Vertex> list_book = { Vertex(1117,-331), Vertex(1037,-383), Vertex(1030,-179),
		Vertex(934, -227), Vertex(875, -188), Vertex(769, -244), Vertex(835, -327), 
		Vertex(813, -419), Vertex(737,-362), Vertex(709,-536), Vertex(795,-649), 
		Vertex(890, -594), Vertex(991, -680), Vertex(968, -491), Vertex(1109,-535) };

	vector<Vertex> list1 = { Vertex(0.1, 0.1), Vertex(0.15, 0.7), Vertex(0.3, 0.8),
		Vertex(0.6, 0.75), Vertex(0.7, 0.5), Vertex(0.5, 0.6), Vertex(0.2, 0.4) };

	vector<Vertex> list2 = { Vertex(0.1, 0.1), Vertex(0.15, 0.7), Vertex(0.3, 0.8),
		Vertex(0.6, 0.75), Vertex(0.7, 0.5), /*Vertex(0.5, 0.6),*/ Vertex(0.2, 0.4) };

	assignIDstoVertices(list_book);
	assignIDstoVertices(list1);
	assignIDstoVertices(list2);

	vector<Vertex> reference(list_book);
	scalePointSet(reference, list_book);

	data.construct_SimplePolygon(list_book);

	Triangulation tri;
	tri.triangulate_simple_Polygon(data);

	//tri.makeMonotone(data);
	//tri.triangulate_MonotonePolygon(data, 4);

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

void assignIDstoVertices(vector<Vertex>& list)
{
	for (int i = 0; i < list.size(); i++)
		list[i].setID(i + 1);
}