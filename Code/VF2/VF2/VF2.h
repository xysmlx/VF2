#ifndef VF2_H
#define VF2_H

#include "head.h"
#include "Graph.h"

class VF2
{
public:
	VF2() {}
	void init();

public:
	vector<Graph> graph;
	Graph query;

};

#endif