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

extern enum MAKE_STEP;
//extern MAKE_STEP currentSTEP;

using namespace std;

void draw_DCEL(const DCEL& data);

void highlight_vertex(const Vertex& v, GLfloat color[]);

void highlight_edge(const DCEL& data, int nFace, int nEdge);

void highlight_edge(Edge* e, GLfloat color[], bool show_destination_Vertex = false);

void highlight_face(Face* f);

void draw_points(const vector<Point2D>& input_pts);

void draw_2D_text(int FaceIdx, int EdgeIdx, int VertexIdx);

void draw_2D_text(MAKE_STEP step);

