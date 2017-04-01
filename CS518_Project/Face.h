#pragma once
#include <vector>

class Edge;

class Face
{
	Edge*		  OuterComponent;
	vector<Edge*> InnerComponents;
public:
	Face(){ OuterComponent = nullptr; InnerComponents.clear(); }
	Face(Edge *OuterComponent_, vector<Edge*> InnerComponents_)
	{
		OuterComponent = OuterComponent_; InnerComponents = InnerComponents_;
	}

	void setOuterComponent(Edge* e){ OuterComponent = e; }
	void setInnerComponents(vector<Edge*> elist){ InnerComponents = elist; }
	void addInnerComponent(Edge* e){ InnerComponents.push_back(e); }

	Edge*			get_outerComponent() const { return OuterComponent; }
	vector<Edge*>	get_innerComponent() const { return InnerComponents; }

	void print() const;
};