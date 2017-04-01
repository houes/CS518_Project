#pragma once
#include "DCEL.h"
#include <vector>

extern DCEL	data;

void runTestCases(int caseID)
{
	data.create_an_edge(Vertex(0.1, 0.1), Vertex(0.15, 0.7));

	data.add_vertex_at(Vertex(0.3, 0.8));
	data.add_vertex_at(Vertex(0.6, 0.7));
	data.add_vertex_at(Vertex(0.7, 0.5));
	data.add_vertex_at(Vertex(0.5, 0.6));
	data.add_vertex_at(Vertex(0.2, 0.4));
	data.add_vertex_at(Vertex(0.4, 0.3));
	data.add_vertex_at(Vertex(0.3, 0.2));

}