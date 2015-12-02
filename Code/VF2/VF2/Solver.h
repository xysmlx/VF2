#ifndef SOLVER_H
#define SOLVER_H

#include "head.h"
#include "Graph.h"
#include "VF2.h"

class Solver
{
public:
	void init(); // init
	void input(); // input
	void solve(); // solve
	void output(); // output

	void ReadFile(string path, vector<Graph> &vec); // Read file from path, write graph data to vec
	void ReadDB(string path); // Read DB file
	void ReadQuery(string path); // Read Query file

	void PrintQueryAns(int id, int cnt); // Pring query ans, id = query file id, cnt = match num

public:
	VF2 vf2; // VF2 main component
	string dbPath; // DB file path
	vector<string> queryPath; // Query file path vector
	vector<string> outputPath; // Output ans file path

	vector<Graph> DBGraph; // Store DB
	vector<Graph> QueryGraph; // Store Query
};

#endif