#pragma once
#include "OpenGLSettings.h"
#include "draw_objects.h"
#include "DCEL.h"
#include "PointLocation.h"
#include "helperFunctions.h"
#include "Triangulation.h"

using namespace std;

extern DCEL data;
extern int the_n_Face;
extern int the_n_Edge;
extern Vertex probe;
extern Face* hitting_face;
extern Edge* hitting_edge;
extern int windowSize_x;
extern int windowSize_y;
extern bool showHalfEdge;
extern double delta;  
extern double omega;
extern vector<Vertex> c_v_list;
extern bool user_customized_vertices;

double cursorX;
double cursorY;
enum MAKE_STEP{ADD_VERTEX,POLYGON, MONOTONE, TRIANGULATION };
MAKE_STEP currentSTEP = MAKE_STEP::ADD_VERTEX;

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

	if (!user_customized_vertices || currentSTEP != MAKE_STEP::ADD_VERTEX)
		highlight_edge(data, the_n_Face, the_n_Edge);

	if (user_customized_vertices)
		draw_2D_text(currentSTEP);

	for (int i = 0; i < c_v_list.size(); i++)
		highlight_vertex(c_v_list[i]);

	highlight_vertex(probe);

	if (hitting_edge != nullptr)
		highlight_edge(hitting_edge, red);
	if (hitting_face != nullptr)
		highlight_face(hitting_face);

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
	Triangulation tri;

	switch (key)
	{
		case  'f':
			the_n_Face++;
			break;
		case  'e':
			the_n_Edge++;
			break;
		case 'h':
		{
			showHalfEdge = !showHalfEdge;

			if (delta == 0.005)
				delta = 0;
			else
				delta = 0.005;

			if (omega == 0.035)
				omega = 0;
			else
				omega = 0.035;

			break;
		}
		case  'm':
			switch (currentSTEP)
			{
				case MAKE_STEP::ADD_VERTEX:
					if (!c_v_list.empty())
					{
						if (!data.construct_SimplePolygon(c_v_list))
							currentSTEP = MAKE_STEP::TRIANGULATION;
						else
							currentSTEP = MAKE_STEP::POLYGON;
					}
					break;
				case MAKE_STEP::POLYGON:
					tri.makeMonotone(data);
					currentSTEP = MAKE_STEP::MONOTONE;
					break;
				case MAKE_STEP::MONOTONE:
					tri.triangulate_simple_Polygon(data);
					data.assignIDsAllEntities();
					currentSTEP = MAKE_STEP::TRIANGULATION;
					break;
				case MAKE_STEP::TRIANGULATION:
					c_v_list.clear();
					data.clear();
					hitting_face = nullptr;
					hitting_edge = nullptr;
					currentSTEP = MAKE_STEP::ADD_VERTEX;
					break;
				default: break;
			}
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
	cursorX = x / (double)windowSize_x;
	cursorY = (windowSize_y - y) / (double)windowSize_y;

	probe.setX(cursorX);
	probe.setY(cursorY);

	glutPostRedisplay();
}

void myMouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		if (!user_customized_vertices || currentSTEP != MAKE_STEP::ADD_VERTEX)
		{
			// 1. point location class
			PointLocation pl;
			hitting_edge = pl.find_edge_right_below_vertex(&data, probe);

			if (hitting_edge != nullptr)
				hitting_face = pl.find_face_contains_vertex(hitting_edge, probe);
			else
				hitting_face = data.get_outmost_face();

			cout << "face# " << hitting_face->getID() << endl;
		}
		else
		{
			// 2. customized vertices - add
			if (currentSTEP == MAKE_STEP::ADD_VERTEX)
				c_v_list.push_back(Vertex(cursorX, cursorY));
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		

	
	}
}