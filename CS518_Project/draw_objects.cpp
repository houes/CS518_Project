#include "draw_objects.h"
#include "helperFunctions.h"


void draw_points(const vector<Point2D>& input_pts)
{
	// scale the pts for drawing purpose
	// coordinate value is restricted to [0,1]
	vector<Point2D> pts = get_scaled_pts_set(input_pts);

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
