/**
	CS518 Project:	DCEL, Polygon triangulation 
					and Plannar point location using persistent search trees.
	Author:		Guangyu Hou
	Institute:	Iowa State University
	Date:		3/30/2017
**/
#pragma once
#include <vector>
#include <iostream>
#include "OpenGLSettings.h"
#include "testcases.h"
#include "DCEL.h"

using namespace std;

DCEL data;


int main(int argc, char** argv)
{
	runTestCases(1);

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
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(300, 50);
	glutCreateWindow("CS518-Project:  Polygon Triangulation");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
