#pragma once
#include "draw_objects.h"
#include "helperFunctions.h"
#include <sstream>

double delta = 0.005; // distance defining an edge separated into two halfedges 
double omega = 0.035; // the length of the arrow head

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


void highlight_edge(const DCEL& data, int nFace, int nEdge)
{
	glLineWidth(2.0);

	nFace = nFace%data.get_faces()->size();

	const list<Face>* faces = data.get_faces();

	list<Face>::const_iterator it = faces->begin();

	int iFace = 0;
	while (iFace++ < nFace)
	{
		it++;
		if (it == faces->end())
			it = faces->begin();
	}

	Edge* s = it->get_outerComponent();
	Edge* e = s;
	vector<Edge*> eList;

	if (s != nullptr)
	{ 
		do
		{
			eList.push_back(e);
			e = e->get_next();
		} while (e != s);
	}

	if (!it->get_innerComponent().empty())
	{
		int nHoles = it->get_innerComponent().size();
		for (int i = 0; i < nHoles; i++)
		{
			Edge* h_s = it->get_innerComponent().at(i);
			Edge* h_e = h_s;
			do
			{
				eList.push_back(h_e);
				h_e = h_e->get_next();
			} while (h_e != h_s);
		}
	}

	nEdge = nEdge % eList.size();
	e = eList.at(nEdge);

	Vertex* v1 = e->get_origin();
	Vertex* v2 = e->get_destination();

	// draw the halfedge, shifted by a distance delta
	double dx = delta *(v1->getY() - v2->getY()) / (*v1 - *v2).length();
	double dy = -delta *(v1->getX() - v2->getX()) / (*v1 - *v2).length();
		
	glColor3f(0.8, 0.8, 0);
	glBegin(GL_LINES);
		glVertex2f(v1->getX() + dx, v1->getY() + dy);
		glVertex2f(v2->getX() + dx, v2->getY() + dy);
	glEnd();

	// draw the arrow heads
	Point2D p1, p2, p3;
	p1 = *v2;
	generate_an_arrow_head(10, omega, *v1, *v2, p2, p3);

	glBegin(GL_TRIANGLES);
		glVertex2f(p1.getX() + dx, p1.getY() + dy);
		glVertex2f(p2.getX() + dx, p2.getY() + dy);
		glVertex2f(p3.getX() + dx, p3.getY() + dy);
	glEnd();

	// draw the destination point: v2
	glColor3f(1, 0, 0);
	glPointSize(7);
	glBegin(GL_POINTS);
		glVertex2f(v2->getX() + dx, v2->getY() + dy);
	glEnd();

	// find e in the storage "edges"
	list<Edge>::const_iterator it2 = data.get_edges()->begin();
	int idx2 = 0;
	while (it2 != data.get_edges()->end())
	{
		if (e == &*it2)
			break;

		idx2++;
		it2++;
	}

	// find v2 in the storage "vertices"
	list<Vertex>::const_iterator it3 = data.get_vertices()->begin();
	int idx3 = 0;
	while (it3 != data.get_vertices()->end())
	{
		if (v2 == &*it3)
			break;

		idx3++;
		it3++;
	}

	draw_2D_text(nFace,idx2,idx3);
}

/*
Drawing text 2D screen.
*/
void drawText(const char *text, int length, int x, int y)
{
	glMatrixMode(GL_PROJECTION); // change the current matrix to PROJECTION
	double matrix[16]; // allocate 16-byte in memory (thanks to BlueByteGames about memory-leak warning comment on YouTube)
	glGetDoublev(GL_PROJECTION_MATRIX, matrix); // get the values from PROJECTION matrix to local variable
	glLoadIdentity(); // reset PROJECTION matrix to identity matrix
	glOrtho(0, 800, 0, 800, -5, 5); // orthographic perspective
	glMatrixMode(GL_MODELVIEW); // change current matrix to MODELVIDE matrix again
	glLoadIdentity(); // reset it to identity matrix
	glPushMatrix(); // push current state of MODELVIEW matrix to stack
	glLoadIdentity(); // reset it again. (may not be required, but it my convention
	glRasterPos2i(x, y); // raster position in 2D
	for (int i = 0; i<length; i++){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]); // generation of characters in our text with 9 by 15 GLU font
	}
	glPopMatrix(); // get MODELVIEW matrix value from stack
	glMatrixMode(GL_PROJECTION); // change current matrix mode to PROJECTION
	glLoadMatrixd(matrix); // reset
	glMatrixMode(GL_MODELVIEW); // change current matrix mode to MODELVIEW
}

void draw_2D_text(int FaceIdx, int EdgeIdx, int VertexIdx)
{
	using namespace std;
	/*Disable lighting effect because the plain text should not rely on light*/
	//glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	// Display of computational results
	ostringstream stringStream[3];
	stringStream[0] << " Current Face  #: " << FaceIdx;
	stringStream[1] << " Current Edge  #: " << EdgeIdx;
	stringStream[2] << " Current Vertex#: " << VertexIdx;


	string text[] = { stringStream[0].str(), stringStream[1].str(), stringStream[2].str() };

	glColor3f(0, 0, 0);
	drawText(text[0].data(), text[0].size(), 0, 780);
	drawText(text[1].data(), text[1].size(), 0, 760);
	drawText(text[1].data(), text[1].size(), 0, 740);
	
	// Display instruction of keybord controls
	stringstream keyboardctrls[5], title;
	title << " keyboard instructions:";
	keyboardctrls[0] << " 'f': change face" ;
	keyboardctrls[1] << " 'e': change edge " ;

	drawText(title.str().data(), title.str().size(), 500, 780);
	drawText(keyboardctrls[0].str().data(), keyboardctrls[0].str().size(), 500, 760);
	drawText(keyboardctrls[1].str().data(), keyboardctrls[1].str().size(), 500, 740);

	glDisable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHTING);

}