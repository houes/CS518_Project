#pragma once
#include "OpenGLSettings.h"
#include "draw_objects.h"
#include "DCEL.h"

using namespace std;

extern DCEL data;


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
	double red[]  { 1, 0, 0 };
	double green[]{ 0, 1, 0 };
	double blue[] { 0, 0, 1 };
	double yellow[]{0.7, 0.7, 0};
	double cran[] { 0, 1, 1 };
	double* colors[] = {red,green,blue,yellow,cran};
	
	draw_DCEL(data);

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
    /*  select clearing (background) color       */
    glClearColor (1.0, 1.0, 1.0, 0.0);

    /* setup the camera location and viewing direction */
    init_camera();

}