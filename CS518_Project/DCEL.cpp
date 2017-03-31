#include"DCEL.h"

void DCEL::add_vertex(const Vertex& v)
{
	vertices.push_back(v);
}

void DCEL::add_edge(const Edge& e)
{
	edges.push_back(e);
}
