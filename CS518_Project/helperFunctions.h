#pragma once
#include <vector>
#include "Vertex.h"


bool smallerX(Point2D p1, Point2D p2);

bool smallerY(Point2D p1, Point2D p2);

vector<Point2D> getBoundaryBox(vector<Point2D> ctrl_pts);

void scalePointSet(const vector<Point2D>& ctrl_pts, vector<Point2D> &pts);
void scalePointSet(const vector<Vertex>& ctrl_pts, vector<Vertex> &pts);
void scalePointSet(vector<Vertex> &pts);

vector<Point2D> get_scaled_pts_set(const vector<Point2D>& input);

void generate_an_arrow_head(double beta, double length, Point2D ps, Point2D pt, Point2D& p1, Point2D& p2);
