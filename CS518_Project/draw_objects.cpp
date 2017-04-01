#pragma once
#include "draw_objects.h"
#include "helperFunctions.h"

void draw_points(const vector<Point2D>& input_pts)
{
	// scale the pts for drawing purpose
	// coordinate value is restricted to [0,1]
	vector<Point2D> pts = get_scaled_pts_set(input_pts);
	//vector<Point2D> pts = input_pts;

	// draw the points
	glLineWidth(2.0);
	glColor3f(0,0,0);

	glPointSize(5);
	glBegin(GL_POINTS);
		for (int i = 0; i < pts.size(); i++)
			glVertex2f(pts[i].getX(), pts[i].getY());
	glEnd();

	// draw the line segments
	glBegin(GL_LINES);
	for (int i = 0; i < pts.size() - 1; i++)
	{
		glVertex2f(pts[i].getX(),	pts[i].getY()  );
		glVertex2f(pts[i+1].getX(), pts[i+1].getY());
	}
	glEnd();

}

void draw_DCEL(const DCEL& data)
{
	// TODO
	// current display range [0,1]x[0,1]
	// need to modify the coordinates of vertices to fit to screen, range to [0,1]

	glLineWidth(2.0);
	glColor3f(0, 0, 0);

	const list<Face>* faces = data.get_faces();

	list<Face>::const_iterator it = faces->begin();

	while (it != faces->end())
	{

		Edge* s = it->get_outerComponent();
		Edge* e = s;
		
		glBegin(GL_LINES);
		if (e!=nullptr)
		do
		{
			Vertex* v1 = e->get_origin();
			Vertex* v2 = e->get_destination();

			glVertex2f(v1->getX(), v1->getY());
			glVertex2f(v2->getX(), v2->getY());

			e = e->get_next();
		} while (e != nullptr && e != s);
		glEnd();

		// traverse edges of each hole of a face
		for (int i = 0; i < it->get_innerComponent().size(); i++)
		{
			s = it->get_innerComponent().at(i);
			e = s;

			glBegin(GL_LINES);
			if (e != nullptr)
			do
			{
				Vertex* v1 = e->get_origin();
				Vertex* v2 = e->get_destination();

				glVertex2f(v1->getX(), v1->getY());
				glVertex2f(v2->getX(), v2->getY());
				
				e = e->get_next();
			} while (e != nullptr && e != s);
			glEnd();
		}


		it++;
	}

}
