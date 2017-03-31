#pragma once
#include"Point.h"
#include<vector>

extern vector<Point2D>	inputPts;

void runTestCases(int caseID)
{
	// test case 1
	vector<Point2D> ctrPts1({ Point2D(0,0),    Point2D(1,0),  Point2D(0.9,1), Point2D(2.5,1),
		Point2D(3,-0.5), Point2D(2,-1), Point2D(1,-0.7) });

	// tests begins
	switch (caseID)
	{
	case 1:
		/* case 1*/
		inputPts = ctrPts1;
		break;
		default:
			break;
	}
}