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
	glPointSize(5);

	const list<Face>* faces = data.get_faces();

	list<Face>::const_iterator it = faces->begin();

	double delta = 0.005;
	double omega = 0.035;

	while (it != faces->end())
	{

		Edge* s = it->get_outerComponent();
		Edge* e = s;
		
		// 1.draw the outerComponent of this face
		// 1.1 line segments
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		if (e!=nullptr)
		do
		{
			Vertex* v1 = e->get_origin();
			Vertex* v2 = e->get_destination();

			// draw the two halfedges, shifted by a distance delta
			double dx =  delta *(v1->getY() - v2->getY()) / (*v1 - *v2).length();
			double dy = -delta *(v1->getX() - v2->getX()) / (*v1 - *v2).length();

			glVertex2f(v1->getX() + dx, v1->getY() + dy);
			glVertex2f(v2->getX() + dx, v2->getY() + dy);

			e = e->get_next();
		} while (e != nullptr && e != s);
		glEnd();

		// 1.2 Points
		glColor3f(0, 0, 0);
		glBegin(GL_POINTS);
			e = s;
			if (e != nullptr)
			do
			{
				Vertex* v = e->get_origin();

				glVertex2f(v->getX(), v->getY());

				e = e->get_next();
			} while (e != nullptr && e != s);
		glEnd();

		// 1.3 arrows heads for segments
		glColor3f(0, 0, 0);
		e = s;
		if (e != nullptr)
			do
			{
				Vertex* v1 = e->get_origin();
				Vertex* v2 = e->get_destination();

				double dx =  delta *(v1->getY() - v2->getY()) / (*v1 - *v2).length();
				double dy = -delta *(v1->getX() - v2->getX()) / (*v1 - *v2).length();

				Point2D p1, p2, p3;
				p1 = *v2;

				generate_an_arrow_head(10, omega, *v1, *v2, p2, p3);

				glBegin(GL_TRIANGLES);
					glVertex2f(p1.getX() + dx, p1.getY() + dy);
					glVertex2f(p2.getX() + dx, p2.getY() + dy);
					glVertex2f(p3.getX() + dx, p3.getY() + dy);
				glEnd();

				e = e->get_next();
			} while (e != nullptr && e != s);


		// 2.draw the inner components of this face (holes)
		glColor3f(0, 0, 1);
		for (int i = 0; i < it->get_innerComponent().size(); i++)
		{
			s = it->get_innerComponent().at(i);
			e = s;

			// 2.1 line segments
			glBegin(GL_LINES);
				if (e != nullptr)
				do
				{
					Vertex* v1 = e->get_origin();
					Vertex* v2 = e->get_destination();

					// draw the two halfedges, shifted by a distance delta
					double dx = delta *(v1->getY() - v2->getY()) / (*v1 - *v2).length();
					double dy = -delta *(v1->getX() - v2->getX()) / (*v1 - *v2).length();

					glVertex2f(v1->getX() + dx, v1->getY() + dy);
					glVertex2f(v2->getX() + dx, v2->getY() + dy);

					e = e->get_next();
				} while (e != nullptr && e != s);
			glEnd();

			// 2.2 points
			glColor3f(0, 0, 0);
			glBegin(GL_POINTS);
				e = s;
				if (e != nullptr)
				do
				{
					Vertex* v = e->get_origin();

					glVertex2f(v->getX(), v->getY());

					e = e->get_next();
				} while (e != nullptr && e != s);
			glEnd();

			// 2.3 arrows heads for segments
			glColor3f(0, 0, 1);
			e = s;
			if (e != nullptr)
				do
				{
					Vertex* v1 = e->get_origin();
					Vertex* v2 = e->get_destination();

					double dx = delta *(v1->getY() - v2->getY()) / (*v1 - *v2).length();
					double dy = -delta *(v1->getX() - v2->getX()) / (*v1 - *v2).length();

					Point2D p1, p2, p3;
					p1 = *v2;

					generate_an_arrow_head(10, omega, *v1, *v2, p2, p3);

					glBegin(GL_TRIANGLES);
						glVertex2f(p1.getX() + dx, p1.getY() + dy);
						glVertex2f(p2.getX() + dx, p2.getY() + dy);
						glVertex2f(p3.getX() + dx, p3.getY() + dy);
					glEnd();

				e = e->get_next();
				} while (e != nullptr && e != s);
		}


		it++;
	}

}
