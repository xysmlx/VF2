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

bool VF2::CheckPrev(const State &s, int a, int b)
{
	return 0;
}

bool VF2::CheckSucc(const State &s, int a, int b)
{
	return 0;
}

bool VF2::CheckIn(const State &s, int a, int b)
{
	return 0;
}

bool VF2::CheckOut(const State &s, int a, int b)
{
	return 0;
}

bool VF2::CheckNew(const State &s, int a, int b)
{
	return 0;
}

bool VF2::check(const State &s, int a, int b)
{
	aSucc.clear();
	aPrev.clear();
	bSucc.clear();
	bPrev.clear();
	// aSucc
	for (int i = pat.head[a];~i;i = pat.edge[i].next)
		aSucc.push_back(pat.edge[i].v);
	// aPrev
	for (int i = revpat.head[a];~i;i = revpat.edge[i].next)
		aPrev.push_back(revpat.edge[i].v);
	// bSucc
	for (int i = g.head[b];~i;i = g.edge[i].next)
		bSucc.push_back(g.edge[i].v);
	// bPrev
	for (int i = revg.head[b];~i;i = revg.edge[i].next)
		bPrev.push_back(revg.edge[i].v);

	if (CheckPrev(s, a, b) && CheckSucc(s, a, b) && CheckIn(s, a, b)
		&& CheckOut(s, a, b) && CheckNew(s, a, b)) return 1;
	return 0;
}

void VF2::GenPairs(const State &s)
{
	flagIn = flagOut = flagAll = 0;
	allPairs.clear();

	vector<int> t1, t2;

	t1.clear();
	t2.clear();
	for (int i = 0;i < pat.vn;i++)
		if (s.out1[i]) t1.push_back(i);
	for (int i = 0;i < g.vn;i++)
		if (s.out2[i]) t2.push_back(i);
	for (int i = 0;i < (int)t1.size();i++)
		for (int j = 0;j < (int)t2.size();j++)
			allPairs.push_back(make_pair(t1[i], t2[j]));
	if (!allPairs.empty())
	{
		flagOut = 1;
		return;
	}

	t1.clear();
	t2.clear();
	for (int i = 0;i < pat.vn;i++)
		if (s.in1[i]) t1.push_back(i);
	for (int i = 0;i < g.vn;i++)
		if (s.in2[i]) t2.push_back(i);
	for (int i = 0;i < (int)t1.size();i++)
		for (int j = 0;j < (int)t2.size();j++)
			allPairs.push_back(make_pair(t1[i], t2[j]));
	if (!allPairs.empty())
	{
		flagIn = 1;
		return;
	}

	t1.clear();
	t2.clear();
	for (int i = 0;i < pat.vn;i++)
		if (s.core1[i] == -1) t1.push_back(i);
	for (int i = 0;i < g.vn;i++)
		if (s.core2[i] == -1) t2.push_back(i);
	for (int i = 0;i < (int)t1.size();i++)
		for (int j = 0;j < (int)t2.size();j++)
			allPairs.push_back(make_pair(t1[i], t2[j]));
	flagAll = 1;
}

void VF2::CheckPairs(const State &s)
{
	candiPairs.clear();

	for (auto ite = allPairs.begin();ite != allPairs.end();ite++)
		if (check(s, ite->first, ite->second)) candiPairs.push_back(*ite);
}

void VF2::UpdateState(State &s, int a, int b)
{
	// Update core,in,out
	for (int i = 0;i < pat.vn;i++)
	{
		s.core1[a] = b;
		s.in1[a] = 0;
		s.out1[a] = 0;
	}
	for (int i = 0;i < g.vn;i++)
	{
		s.core2[b] = a;
		s.in2[b] = 0;
		s.out2[b] = 0;
	}

	// Add new out1
	for (int i = pat.head[a];~i;i = pat.edge[i].next)
	{
		int v = pat.edge[i].v;
		if (s.core1[v] == -1) s.out1[v] = 1;
	}
	// Add new in1
	for (int i = revpat.head[a];~i;i = revpat.edge[i].next)
	{
		int v = revpat.edge[i].v;
		if (s.core1[v] == -1) s.in1[v] = 1;
	}
	// Add new out2
	for (int i = g.head[b];~i;i = g.edge[i].next)
	{
		int v = g.edge[i].v;
		if (s.core2[v] == -1) s.out2[v] = 1;
	}
	// Add new in2
	for (int i = revg.head[b];~i;i = revg.edge[i].next)
	{
		int v = revg.edge[i].v;
		if (s.core2[v] == -1) s.in2[v] = 1;
	}
}

bool VF2::dfs(const State &s)
{
	// Matched
	if ((int)s.s.size() == pat.vn)
	{
		tlist = s.s;
		return 1;
	}

	// Generate Pair(n,m)
	GenPairs(s);
	// Check allPairs, get candiPairs
	CheckPairs(s);

	// Next recursive
	for (auto ite = candiPairs.begin();ite != candiPairs.end();ite++)
	{
		State ns = s;
		int a = ite->first;
		int b = ite->second;
		UpdateState(ns, a, b);
		dfs(ns);
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