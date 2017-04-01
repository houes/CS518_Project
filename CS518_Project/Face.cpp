#pragma once
#include "Vertex.h"
#include "Face.h"
#include "Edge.h"

void Face::print() const
{
	// prints both outer and innner edges.

	// traverse outer edges of a face
	Edge* s = OuterComponent;
	Edge* e = s;

	cout << "outer edges: " << endl;

	if (e != nullptr)
		do{
		e->get_origin()->print();
		e = e->get_next();
		} while (e != nullptr && e != s);
	else
		cout << "NULL"<<endl;

	cout << "inner edges: " << endl;
	// traverse edges of each hole of a face
	if (InnerComponents.empty())
		cout << "NULL";
	else
		for (int i = 0; i < InnerComponents.size(); i++)
		{
			s = InnerComponents.at(i);
			e = s;

			if (e!=nullptr)
			do
			{
				e->get_origin()->print();
				e = e->get_next();
			} while (e != nullptr && e != s);

			cout << endl;

		}

	cout << endl;

}