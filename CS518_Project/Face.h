#pragma once
#include <vector>

class Edge;

class Face
{
	int ID;

	Edge*		  OuterComponent;
	vector<Edge*> InnerComponents;
public:
	Face(){ ID = -1; OuterComponent = nullptr; InnerComponents.clear(); }
	Face(Edge *OuterComponent_, vector<Edge*> InnerComponents_)
	{
		ID = -1;
		OuterComponent = OuterComponent_; 
		InnerComponents = InnerComponents_;
	}

	void setID(int ID_){ ID = ID_; }
	int  getID(){ return ID; }

	void setOuterComponent(Edge* e){ OuterComponent = e; }
	void setInnerComponents(vector<Edge*> elist){ InnerComponents = elist; }
	void addInnerComponent(Edge* e){ InnerComponents.push_back(e); }
	bool hasInnerComponent() const { return !InnerComponents.empty(); }

	Edge*			get_outerComponent() const { return OuterComponent; }
	vector<Edge*>	get_innerComponent() const { return InnerComponents; }

	void print() const;
};