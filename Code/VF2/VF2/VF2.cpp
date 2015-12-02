#include "VF2.h"

void VF2::init(const vector<Graph> &db)
{
	DBGraph.clear();
	DBGraph = db;
	match.clear();
}

void VF2::GenRevGraph(const Graph &src, Graph &dst)
{
	dst = Graph();
	for (int i = 0;i < src.vn;i++)
		dst.addv(src.vtx[i].id, src.vtx[i].label);

	for (int i = 0;i < src.en;i++)
		dst.addse(src.edge[i].v, src.edge[i].u, src.edge[i].label);
}

bool VF2::check(const State &s, int a, int b)
{
	return 0;
}

bool VF2::dfs(State s)
{
	// Matched
	if ((int)s.s.size() == pat.vn)
	{
		tlist = s.s;
		return 1;
	}

	// Generate Pair(n,m)
	vector<int> tQ, tDB;
	bool visQ[Graph::maxv], visDB[Graph::maxv];
	memset(visQ, 0, sizeof(visQ));
	memset(visDB, 0, sizeof(visDB));
	// Cal tQ
	for (int _ = 0;_ < pat.vn;_++)
	{
		for (int i = pat.head[_];~i;i = pat.edge[i].next)
		{
			int v = pat.edge[i].v;
			if (!s.visQ[v]) visQ[v] = 1;
		}
	}
	for (int i = 0;i < pat.vn;i++)
		if (visQ[i]) tQ.push_back(i);
	//Cal tDB
	for (int _ = 0;_ < g.vn;_++)
	{
		for (int i = g.head[_];~i;i = g.edge[i].next)
		{
			int v = g.edge[i].v;
			if (!s.visDB[v]) visDB[v] = 1;
		}
	}
	for (int i = 0;i < g.vn;i++)
		if (visDB[i]) tDB.push_back(i);
	// Solve tQ empty
	if (tQ.empty())
	{
		for (int i = 0;i < pat.vn;i++)
			if (!s.visQ[i]) tQ.push_back(i);
	}
	// Solve tDB empty
	if (tDB.empty())
	{
		for (int i = 0;i < g.vn;i++)
			if (!s.visDB[i]) tDB.push_back(i);
	}

	// Next recursive
	for (int i = 0;i < (int)tDB.size();i++)
	{
		//
	}

	return 0;
}

bool VF2::query()
{
	return dfs(State());
}

int VF2::vf2(const Graph &QG, const int &QID)
{
	QueryGraph = QG;
	QueryID = QID;

	pat = QueryGraph;
	GenRevGraph(pat, revpat);

	int ret = 0;
	for (int i = 0;i < (int)DBGraph.size();i++)
	{
		g = DBGraph[i];
		GenRevGraph(g, revg);
		if (query()) // Matched
		{
			match.push_back(Match(tlist, i));
			ret++;
		}
	}
	return ret;
}