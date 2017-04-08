#pragma once
#include <vector>
#include "DCEL.h"
#include "Triangulation.h"
#include "helperFunctions.h"
#include "PointLocation.h"


extern DCEL	data;
extern Vertex probe;
extern Face* hitting_face;
extern Edge* hitting_edge;
extern double cursorX;
extern double cursorY;

void assignIDstoVertices(vector<Vertex>& list);

void runTestCases(int caseID, int sampleID, int faceIdx_)
{
	// 1. three data sets - three set of vertices to test

	// 1.1 a simple monotone polygon
	vector<Vertex> list1 = { Vertex(0.1, 0.1), Vertex(0.15, 0.7), Vertex(0.3, 0.8),
		Vertex(0.6, 0.75), Vertex(0.7, 0.5), Vertex(0.2, 0.4) };
	
	// 1.2 a simple non-monotone polygon
	vector<Vertex> list2 = { Vertex(0.1, 0.1), Vertex(0.15, 0.7), Vertex(0.3, 0.8),
		Vertex(0.6, 0.75), Vertex(0.7, 0.5), Vertex(0.5, 0.6), Vertex(0.2, 0.4) };

	// 1.3 anther simple non-monotone polygon (as shown in the book and class)
	vector<Vertex> list3 = { Vertex(1117,-331), Vertex(1037,-383), Vertex(1030,-179),
		Vertex(934, -227), Vertex(875, -188), Vertex(769, -244), Vertex(835, -327), 
		Vertex(813, -419), Vertex(737,-362), Vertex(709,-536), Vertex(795,-649), 
		Vertex(890, -594), Vertex(991, -680), Vertex(968, -491), Vertex(1109,-535) };

	assignIDstoVertices(list1);
	assignIDstoVertices(list2);
	assignIDstoVertices(list3);

	scalePointSet(list1);
	scalePointSet(list2);
	scalePointSet(list3);

	vector<vector<Vertex>> samples = { list1, list2, list3 };

	//// debug -start
	//Triangulation tri;
	//data.construct_SimplePolygon(list3);
	//tri.triangulate_simple_Polygon(data);

	//return;
	//// debug - end

	// 2. test different cases

	// 2.0 choose your test sample
	vector<Vertex> sample = samples[sampleID-1];

	// 2.2 start testing
	switch (caseID)
	{
		case 1:// 2.2.1 construct simple polygon
		{	
			data.construct_SimplePolygon(sample);
			break;
		}
		case 2: // 2.2.2 make simple polygon monotone
		{
			Triangulation tri;
			data.construct_SimplePolygon(sample);
			tri.makeMonotone(data);
			break;
		}
		case 3: // 2.2.3 trianguate all simple monotoned polygons
		{
			Triangulation tri;
			data.construct_SimplePolygon(sample);
			tri.triangulate_simple_Polygon(data);
			break;
		}
		case 4: // 2.2.4 trianguate a simple monotoned polygon in the sample, please specify your face
		{
			//  faceIdx := [0, maxFace# ]
			int faceIdx;
			if (faceIdx_ == -1) // not provided
				faceIdx = 1;
			else				// provided
				faceIdx = faceIdx_; 

			if (faceIdx<0 || faceIdx > data.get_faces()->size() - 1)
				cout << "faceIdx invalid!" << endl;
			else
			{
				Triangulation tri;
				data.construct_SimplePolygon(sample);
				tri.makeMonotone(data);
				tri.triangulate_MonotonePolygon(data, faceIdx);
			}
			break;
		}
		default:
			break;
	}

	data.assignIDsAllEntities();

	//// case 1:
	//data.create_an_edge(Vertex(0.1, 0.1), Vertex(0.15, 0.7));

	//data.add_vertex_at(Vertex(0.3, 0.8));
	//data.add_vertex_at(Vertex(0.6, 0.7));
	//data.add_vertex_at(Vertex(0.7, 0.5));
	//data.add_vertex_at(Vertex(0.5, 0.6));
	//data.add_vertex_at(Vertex(0.2, 0.4));
	////data.add_vertex_at(Vertex(0.4, 0.3));
	////data.add_vertex_at(Vertex(0.3, 0.2));

	//data.split_face(data.get_an_edge_at(1), const_cast<Vertex*>(&data.get_vertices()->back()));
	//data.split_face(data.get_an_edge_at(5), data.get_an_vertex_at(5));
	//data.add_vertex_at(Vertex(0.4, 0.2), data.get_an_edge_at(10));
	//data.add_vertex_at(Vertex(0.9,0.9), data.get_an_edge_at(4));
	//data.split_face(data.get_an_edge_at(15), data.get_an_vertex_at(6));
	//data.split_face(data.get_an_edge_at(14), data.get_an_vertex_at(3));

	// case 2:
	//data.create_an_edge(Vertex(0.1, 0.1), Vertex(0.15, 0.7));

	//data.add_vertex_at(Vertex(0.3, 0.8));
	//data.add_vertex_at(Vertex(0.6, 0.7));
	//data.add_vertex_at(Vertex(0.7, 0.5));
	////data.add_vertex_at(Vertex(0.5, 0.6));
	////data.add_vertex_at(Vertex(0.2, 0.4));
	////data.add_vertex_at(Vertex(0.4, 0.3));
	////data.add_vertex_at(Vertex(0.3, 0.2));

	//data.add_vertex_at(Vertex(0.6, 0.3));
	//data.add_vertex_at(Vertex(0.9, 0.8), data.get_an_edge_at(7));

	//data.split_face(data.get_an_edge_at(1), const_cast<Vertex*>(&data.get_vertices()->back()));

	// case 3:
	//data.create_an_edge(Vertex(0.1, 0.1), Vertex(0.15, 0.7));

	//data.add_vertex_at(Vertex(0.3, 0.8));
	//data.add_vertex_at(Vertex(0.6, 0.7));
	//data.add_vertex_at(Vertex(0.7, 0.5));
	////data.add_vertex_at(Vertex(0.5, 0.6));
	////data.add_vertex_at(Vertex(0.2, 0.4));
	////data.add_vertex_at(Vertex(0.4, 0.3));
	////data.add_vertex_at(Vertex(0.3, 0.2));

	//data.split_face(data.get_an_edge_at(1), const_cast<Vertex*>(&data.get_vertices()->back()));

	//data.add_vertex_at(Vertex(0.6, 0.3));
	//data.add_vertex_at(Vertex(0.9, 0.8), data.get_an_edge_at(7));

	//vector<Vertex> list2 = { Vertex(0.1, 0.1), Vertex(0.15, 0.7), Vertex(0.3, 0.8),
	//	Vertex(0.6, 0.75), Vertex(0.7, 0.5), /*Vertex(0.5, 0.6),*/ Vertex(0.2, 0.4) };

}

void assignIDstoVertices(vector<Vertex>& list)
{
	for (int i = 0; i < list.size(); i++)
		list[i].setID(i + 1);
}