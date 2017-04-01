/**
draw_objects.h
**/

#pragma once
#include <iostream>
#include "DCEL.h"
#include <vector>

#if defined(__APPLE__) || defined(MACOSX)
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <windows.h>
    #include <gl/gl.h>
    #include <gl/glu.h>
    #include <gl/glut.h>
#endif

using namespace std;

void draw_DCEL(const DCEL& data);

void draw_points(const vector<Point2D>& input_pts);


