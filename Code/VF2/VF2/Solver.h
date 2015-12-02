#ifndef SOLVER_H
#define SOLVER_H

#include "head.h"
#include "Graph.h"
#include "VF2.h"

class Solver
{
public:
	void init();
	void input();
	void solve();
	void output();

	void ReadFile(string path, vector<Graph> &vec);
	void ReadDB(string path);
	void ReadQuery(string path);

public:
	VF2 vf2;
	string dbPath;
	vector<string> queryPath;

	vector<Graph> DBGraph;
	vector<Graph> QueryGraph;

};

#endif