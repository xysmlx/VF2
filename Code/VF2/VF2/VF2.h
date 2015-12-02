#ifndef VF2_H
#define VF2_H

#include "head.h"
#include "Graph.h"

class VF2
{
public:
	struct State // State of dfs matching
	{
		vector<prii> s; // Store matched pairs
		int core1[Graph::maxv]; // core1[n] = m or -1
		int core2[Graph::maxv]; // core2[m] = n or -1
		State()
		{
			memset(core1, -1, sizeof(core1));
			memset(core2, -1, sizeof(core2));
		}
	};

	struct Match // Store match
	{
		vector<prii> s; // match
		int id; // graphDB id
		Match() {}
		Match(vector<prii> _s, int _id) :s(_s), id(_id) {}
	};

public:
	VF2() {}
	void init(const vector<Graph> &db); // Init the VF2 class
	void GenRevGraph(const Graph &src, Graph &dst); // Generate reversed graph
	bool check(const State &s, int a, int b); // Check feasibility
	bool dfs(State s); // VF2 dfs (recursive)
	bool query(); // Run VF2 on pat & g (main procedure)
	int vf2(const Graph &QG, const int &QID); // Run VF2 on QueryGraph & DBGraph (engine)

public:
	vector<Graph> DBGraph; // Graph database
	Graph QueryGraph; // Graph for query, pattern
	int QueryID; // Store the Query ID

	vector<Match> match; // Store the matched graph info

	vector<prii> tlist; // Temp var

	Graph pat, g;
	Graph revpat, revg;
};

#endif