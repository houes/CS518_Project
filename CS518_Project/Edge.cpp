#pragma once
#include <stdexcept>
#include "Edge.h"
#include "Vertex.h"
#include "Face.h"
#include "Vector.h"

bool Edge::isOnOuterComponent()
{
	Face* f = this->get_incidentFace();

	if (f == nullptr)
		throw std::invalid_argument("incident face is NULL");
	if (f->get_outerComponent() == nullptr && f->get_innerComponent().empty())
		throw std::invalid_argument("face is not bounded on outer or inner component");

	if (f->get_outerComponent() != nullptr)
	{
		Edge* s = f->get_outerComponent();
		Edge* e = s;
		do 
		{
			if (e == this)
				return true;

			e = e->get_next();

		} while (e != s);
	}

	if (!f->get_innerComponent().empty())
	{
		for (int i = 0; i < f->get_innerComponent().size(); i++)
		{
			Edge* s = f->get_innerComponent().at(i);
			Edge* e = s;
			do
			{
				if (e == this)
					return false;

				e = e->get_next();

			} while (e != s);
		}
	}

	throw std::invalid_argument(" this edge is on neither inner component or outer component, DCEL structure is not correct");
}

Vector Edge::getVector()
{
	Vertex v1(*get_destination());
	Vertex v2(*get_origin());

	return v1 - v2;
}