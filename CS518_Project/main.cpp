/**
	CS518 Project:	DCEL, Polygon triangulation 
					and Plannar point location using persistent search trees.
	Author:		Guangyu Hou
	Institute:	Iowa State University
	Date:		04/06/2017
**/
#pragma once
#include <vector>
#include <iostream>
#include "OpenGLSettings.h"
#include "testcases.h"
#include "DCEL.h"

using namespace std;

DCEL data;
int the_n_Face;
int the_n_Edge;
Vertex probe;
Face* hitting_face = nullptr;
Edge* hitting_edge = nullptr;

int windowSize_x=600;
int windowSize_y=600;

bool user_customized_vertices = false;

int main(int argc, char** argv)
{
	//for debug
	//runTestCases(1, 2);

	int sampleChoice, caseChoice;	// must provide
	int faceIndex;					// optional

	do{
		// please provide your test configuration [sampleChoice, caseChoice]
		cout << " Please provide your test configuration ( int sampleChoice, int caseChoice)" << endl;

		cout << " Sample choices [1-4]" << endl
			<< "  1- A simple monotone polygon" << endl
			<< "  2- A simple non-monotone polygon" << endl
			<< "  3- Anther simple non-monotone polygon(as shown in the book and class, most complicated)"<<endl 
			<< "  4- User defined vertices " << endl;
		cin >> sampleChoice;

		// customized vertices, added using mouse click in OpenGLSetting.cpp
		if (sampleChoice == 4)
		{
			user_customized_vertices = true;
			break;
		}

		cout << " Test cases choices [1-4]" << endl
			<< "  1- Construct simple polygon" << endl
			<< "  2- Make simple polygon monotone" << endl
			<< "  3- Trianguate all simple monotoned polygons" << endl
			<< "  4- Trianguate a simple monotoned polygon in the sample(need to specify your face)" << endl;
		cin >> caseChoice;

		if (caseChoice == 4)
		{
			cout << "provide your face index [0,maxFace#]" << endl;
			cin >> faceIndex;
		}

		if (sampleChoice >= 1 && sampleChoice <= 4 && caseChoice >= 1 && caseChoice <= 4)
		{
			if (caseChoice!=4)
				runTestCases(caseChoice, sampleChoice);
			else
				runTestCases(caseChoice, sampleChoice, faceIndex);

			break;
		}
		else{
			cout << endl << " *** warning [sampleChoice] or [caseChoice] out of range! re-try *** " << endl << endl;
		}
	}
	while (1);

	/*
	// user input
	int     n;    // number of polygon points
	cout << "Please input the number of the points: ";
	cin >> n;
	cout << "Please input the points: " << endl
		<< "(  Note: Points are separated by a space." << endl
		<< "   Coordinates are separted by a comma." << endl
		<< "   For example: 2,1 3,4 ,5,7 are three points)" << endl;
	for (int i = 0; i < n; i++)
	{
		double x, y;
		char comma, space;
		cin >> x;
		cin >> comma;
		cin >> y;
		inputPts.push_back(Point2D(x, y));
	}
	*/

	// verify the data
	data.print();

	// OpenGL initialize
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowSize_x, windowSize_y);
	glutInitWindowPosition(300, 50);
	glutCreateWindow("CS518-Project:  Polygon Triangulation by Guangyu Hou");
	init();
	glutPassiveMotionFunc(myMousePickingFunction);
	// specify the mouse click events to opengl
	glutMouseFunc(myMouseFunc);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
