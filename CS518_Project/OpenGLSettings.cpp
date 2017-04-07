#pragma once
#include "OpenGLSettings.h"
#include "draw_objects.h"
#include "DCEL.h"
#include "PointLocation.h"

using namespace std;

extern DCEL data;
extern int the_n_Face;
extern int the_n_Edge;
extern Vertex probe;
extern Face* hitting_face;
extern Edge* hitting_edge;
extern int windowSize_x;
extern int windowSize_y;

int cursorX;
int cursorY;

/**
 * @brief this initializes the camera.
 *  The code creates a perspective view frustum and
 *  move the camera.
 */
void init_camera(void)
{
    // Switch to the projection matrix mode
    glMatrixMode(GL_PROJECTION);

    // load an identity matrix
    glLoadIdentity();

    // Set the Orthogonal projection (2D)
	glOrtho(0.0, 1.0, 0.0, 1.0 ,-1.0, 1.0);

    // change the matrix mode
    glMatrixMode(GL_MODELVIEW);

    // load an identity matrix
    glLoadIdentity();

}


/**
 * @brief draw_scene
 * This function draws the scene.
 * It is called every frame and renders the object that
 * populate the virtual scene
 */
void draw_scene(void)
{
	GLfloat red[]  { 1, 0, 0 };
	GLfloat green[]{ 0, 1, 0 };
	GLfloat blue[] { 0, 0, 1 };
	GLfloat yellow[]{0.7, 0.7, 0};
	GLfloat cran[] { 0, 1, 1 };
	GLfloat* colors[] = {red,green,blue,yellow,cran};
	
	draw_DCEL(data);

	highlight_edge(data, the_n_Face, the_n_Edge);

	highlight_vertex(probe);
	highlight_edge(hitting_edge, red);
	//highlight_face(hitting_face);

	//vector<Point2D> pts{ Point2D(0, 0), Point2D(1, 1)};
	//draw_points(pts);
}

/**
 * @brief display
 * This is the main display function.
 * It is automatilcally called every frame by the glutMainLoop.
 * It in
 */
void display(void)
{
    /*  clear all pixels  */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*************************************************************************/
    // If you would like to change camera and light parameters during
    // application runtime: do it at this location

    /*************************************************************************/

    /* create a scene */
    draw_scene();

    /*  Wait until renderer is ready and
    *  swap the buffers
    */
    glutSwapBuffers();
}

/**
 * @brief init
 * This function inits the canera and the light.
 * It calls the related functions
 */
void init (void)
{
	// global variables initilization
	the_n_Face = 0;
	the_n_Edge = 0;

    /*  select clearing (background) color       */
    glClearColor (1.0, 1.0, 1.0, 0.0);

    /* setup the camera location and viewing direction */
    init_camera();

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case  'f':
			the_n_Face++;
			break;
		case  'e':
			the_n_Edge++;
			break;
		default:  break;
	}

	/* this redraws the scene without
	waiting for the display callback so that any changes appear
	instantly */
	glutPostRedisplay();

}

/**
* @brief myMousePickingFunction
* This function is called at every mouse move. It starts the picking process.
* @param x - the x position of the mouse pointer on screen.
* @param y - the y position of the mouse pointer on screen.
*/
void myMousePickingFunction(int x, int y)
{
	cursorX = x;
	cursorY = y;

	probe = Vertex(cursorX / 600.0, (600 - cursorY) / 600.0);
}

void myMouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		PointLocation pl;
		hitting_edge = pl.find_edge_above_vertex(&data, probe);
		//hitting_face = pl.find_polygon_contains_vertex(&data, probe);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		
	}
}