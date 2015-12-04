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

	for (int i = 0; i < src.vn; i++)
		dst.addv(src.vtx[i].id, src.vtx[i].label);

	for (int i = 0; i < src.en; i++)
		dst.addse(src.edge[i].v, src.edge[i].u, src.edge[i].label);
}

bool VF2::CheckPrev(const State &s, int a, int b)
{
	vector<int> tmp;
	bool flag;
	vector<int>::iterator ite;

	tmp.resize(Graph::maxv);
	ite = set_intersection(m1.begin(), m1.end(), pred1.begin(), pred1.end(), tmp.begin());
	tmp.erase(ite, tmp.end());
	for (auto ite1 = tmp.begin();ite1 != tmp.end();ite1++)
	{
		flag = 0;
		for (auto ite2 = pred2.begin();ite2 != pred2.end() && !flag;ite2++)
			if (s.core1[*ite1] == *ite2)
			{
				/*int i = -1, j = -1;
				for (i = pat.head[*ite1];~i;i = pat.edge[i].next)
					if (pat.edge[i].v == a) break;
				for (int j = g.head[*ite2];~j;j = g.edge[j].next)
					if (g.edge[j].v == b) break;
				if (pat.edge[i].label == g.edge[j].label) flag = 1;*/
				flag = 1;
			}
		if (!flag) return 0;
	}

	tmp.resize(Graph::maxv);
	ite = set_intersection(m2.begin(), m2.end(), pred2.begin(), pred2.end(), tmp.begin());
	tmp.erase(ite, tmp.end());
	for (auto ite2 = tmp.begin();ite2 != tmp.end();ite2++)
	{
		flag = 0;
		for (auto ite1 = pred1.begin();ite1 != pred1.end() && !flag;ite1++)
			if (s.core2[*ite2] == *ite1)
			{
				/*int i = -1, j = -1;
				for (i = pat.head[*ite1];~i;i = pat.edge[i].next)
					if (pat.edge[i].v == a) break;
				for (int j = g.head[*ite2];~j;j = g.edge[j].next)
					if (g.edge[j].v == b) break;
				if (pat.edge[i].label == g.edge[j].label) flag = 1;*/
				flag = 1;
			}
		if (!flag) return 0;
	}

	return 1;
}

bool VF2::CheckSucc(const State &s, int a, int b)
{
	vector<int> tmp;
	bool flag;
	vector<int>::iterator ite;

	tmp.resize(Graph::maxv);
	ite = set_intersection(m1.begin(), m1.end(), succ1.begin(), succ1.end(), tmp.begin());
	tmp.erase(ite, tmp.end());
	for (auto ite1 = tmp.begin();ite1 != tmp.end();ite1++)
	{
		flag = 0;
		for (auto ite2 = succ2.begin();ite2 != succ2.end() && !flag;ite2++)
			if (s.core1[*ite1] == *ite2)
			{
				/*int i = -1, j = -1;
				for (i = revpat.head[*ite1];~i;i = revpat.edge[i].next)
					if (revpat.edge[i].v == a) break;
				for (int j = revg.head[*ite2];~j;j = revg.edge[j].next)
					if (revg.edge[j].v == b) break;
				if (revpat.edge[i].label == revg.edge[j].label) flag = 1;*/
				flag = 1;
			}
		if (!flag) return 0;
	}

	tmp.resize(Graph::maxv);
	ite = set_intersection(m2.begin(), m2.end(), succ2.begin(), succ2.end(), tmp.begin());
	tmp.erase(ite, tmp.end());
	for (auto ite2 = tmp.begin();ite2 != tmp.end();ite2++)
	{
		flag = 0;
		for (auto ite1 = succ1.begin();ite1 != succ1.end() && !flag;ite1++)
			if (s.core2[*ite2] == *ite1)
			{
				/*int i = -1, j = -1;
				for (i = revpat.head[*ite1];~i;i = revpat.edge[i].next)
					if (revpat.edge[i].v == a) break;
				for (int j = revg.head[*ite2];~j;j = revg.edge[j].next)
					if (revg.edge[j].v == b) break;
				if (revpat.edge[i].label == revg.edge[j].label) flag = 1;*/
				flag = 1;
			}
		if (!flag) return 0;
	}

	return 1;
}

bool VF2::CheckIn(const State &s)
{
	vector<int> tmp;
	int a, b, c, d;
	vector<int>::iterator ite;

	tmp.resize(Graph::maxv);
	ite = set_intersection(succ1.begin(), succ1.end(), tin1.begin(), tin1.end(), tmp.begin());
	tmp.erase(ite, tmp.end());
	a = tmp.size();

	tmp.resize(Graph::maxv);
	ite = set_intersection(succ2.begin(), succ2.end(), tin2.begin(), tin2.end(), tmp.begin());
	tmp.erase(ite, tmp.end());
	b = tmp.size();

	tmp.resize(Graph::maxv);
	ite = set_intersection(pred1.begin(), pred1.end(), tin1.begin(), tin1.end(), tmp.begin());
	tmp.erase(ite, tmp.end());
	c = tmp.size();

	tmp.resize(Graph::maxv);
	ite = set_intersection(pred2.begin(), pred2.end(), tin2.begin(), tin2.end(), tmp.begin());
	tmp.erase(ite, tmp.end());
	d = tmp.size();

	return (a <= b) && (c <= d);
}

bool VF2::CheckOut(const State &s)
{
	vector<int> tmp;
	int a, b, c, d;
	vector<int>::iterator ite;

	tmp.resize(Graph::maxv);
	ite = set_intersection(succ1.begin(), succ1.end(), tout1.begin(), tout1.end(), tmp.begin());
	tmp.erase(ite, tmp.end());
	a = tmp.size();

	tmp.resize(Graph::maxv);
	ite = set_intersection(succ2.begin(), succ2.end(), tout2.begin(), tout2.end(), tmp.begin());
	tmp.erase(ite, tmp.end());
	b = tmp.size();

	tmp.resize(Graph::maxv);
	ite = set_intersection(pred1.begin(), pred1.end(), tout1.begin(), tout1.end(), tmp.begin());
	tmp.erase(ite, tmp.end());
	c = tmp.size();

	tmp.resize(Graph::maxv);
	ite = set_intersection(pred2.begin(), pred2.end(), tout2.begin(), tout2.end(), tmp.begin());
	tmp.erase(ite, tmp.end());
	d = tmp.size();

	return (a <= b) && (c <= d);
}

bool VF2::CheckNew(const State &s)
{
	vector<int> tmp;
	int a, b, c, d;
	vector<int>::iterator ite;

	tmp.resize(Graph::maxv);
	ite = set_intersection(ns1.begin(), ns1.end(), pred1.begin(), pred1.end(), tmp.begin());
	tmp.erase(ite, tmp.end());
	a = tmp.size();

	tmp.resize(Graph::maxv);
	ite = set_intersection(ns2.begin(), ns2.end(), pred2.begin(), pred2.end(), tmp.begin());
	tmp.erase(ite, tmp.end());
	b = tmp.size();

	tmp.resize(Graph::maxv);
	ite = set_intersection(ns1.begin(), ns1.end(), succ1.begin(), succ1.end(), tmp.begin());
	tmp.erase(ite, tmp.end());
	c = tmp.size();

	tmp.resize(Graph::maxv);
	ite = set_intersection(ns2.begin(), ns2.end(), succ2.begin(), succ2.end(), tmp.begin());
	tmp.erase(ite, tmp.end());
	d = tmp.size();

	return (a <= b) && (c <= d);
}

void VF2::CalDFSVec(const State &s)
{
	m1.clear();
	m2.clear();
	tin1.clear();
	tin2.clear();
	tout1.clear();
	tout2.clear();
	n1.clear();
	n2.clear();
	ns1.clear();
	ns2.clear();
	t1.clear();
	t2.clear();

	for (auto ite = s.s.begin(); ite != s.s.end(); ite++)
	{
		m1.push_back(ite->first);
		m2.push_back(ite->second);
	}
	sort(m1.begin(), m1.end());
	sort(m2.begin(), m2.end());

	for (int i = 0; i < pat.vn; i++)
		if (s.out1[i])
			tout1.push_back(i);
	for (int i = 0; i < g.vn; i++)
		if (s.out2[i])
			tout2.push_back(i);

	for (int i = 0; i < pat.vn; i++)
		if (s.in1[i])
			tin1.push_back(i);
	for (int i = 0; i < g.vn; i++)
		if (s.in2[i])
			tin2.push_back(i);

	for (int i = 0; i < pat.vn; i++)
		n1.push_back(i);
	for (int i = 0; i < g.vn; i++)
		n2.push_back(i);

	t1.resize(Graph::maxv);
	auto ite = set_union(tin1.begin(), tin1.end(), tout1.begin(), tout1.end(), t1.begin());
	t1.erase(ite, t1.end());

	t2.resize(Graph::maxv);
	ite = set_union(tin1.begin(), tin1.end(), tout2.begin(), tout2.end(), t2.begin());
	t2.erase(ite, t2.end());

	vector<int> tmp;

	tmp.resize(Graph::maxv);
	ite = set_difference(n1.begin(), n1.end(), m1.begin(), m1.end(), tmp.begin());
	tmp.erase(ite, tmp.end());
	ns1.resize(Graph::maxv);
	ite = set_difference(tmp.begin(), tmp.end(), t1.begin(), t1.end(), ns1.begin());
	ns1.erase(ite, ns1.end());

	tmp.resize(Graph::maxv);
	ite = set_difference(n2.begin(), n2.end(), m2.begin(), m2.end(), tmp.begin());
	tmp.erase(ite, tmp.end());
	ns2.resize(Graph::maxv);
	ite = set_difference(tmp.begin(), tmp.end(), t2.begin(), t2.end(), ns2.begin());
	ns2.erase(ite, ns2.end());
}

void VF2::CalCheckVec(const State &s, int a, int b)
{
	// Init
	pred1.clear();
	pred2.clear();
	succ1.clear();
	succ2.clear();

	// aPred
	for (int i = revpat.head[a]; ~i; i = revpat.edge[i].next)
		pred1.push_back(revpat.edge[i].v);
	// bPred
	for (int i = revg.head[b]; ~i; i = revg.edge[i].next)
		pred2.push_back(revg.edge[i].v);
	// aSucc
	for (int i = pat.head[a]; ~i; i = pat.edge[i].next)
		succ1.push_back(pat.edge[i].v);
	// bSucc
	for (int i = g.head[b]; ~i; i = g.edge[i].next)
		succ2.push_back(g.edge[i].v);

	vector<int> tmp;
	tmp.reserve(Graph::maxv);

	// Sort
	sort(pred1.begin(), pred1.end());
	sort(pred2.begin(), pred2.end());
	sort(succ1.begin(), succ1.end());
	sort(succ2.begin(), succ2.end());
}

bool VF2::check(const State &s, int a, int b)
{
	// Check vertex label
	if (pat.vtx[a].label != g.vtx[b].label) return 0;

	// Check edge label
	//vector<int> 

	CalCheckVec(s, a, b);

	// Feasibility
	if (CheckPrev(s, a, b) && CheckSucc(s, a, b) && CheckIn(s) && CheckOut(s) && CheckNew(s)) return 1;
	return 0;
}

void VF2::GenPairs(const State &s)
{
	CalDFSVec(s);

	flagIn = flagOut = flagAll = 0;
	allPairs.clear();

	for (int i = 0; i < (int)tout1.size(); i++)
		for (int j = 0; j < (int)tout2.size(); j++)
			allPairs.push_back(make_pair(tout1[i], tout2[j]));
	if (!allPairs.empty())
	{
		flagOut = 1;
		return;
	}

	for (int i = 0; i < (int)tin1.size(); i++)
		for (int j = 0; j < (int)tin2.size(); j++)
			allPairs.push_back(make_pair(tin1[i], tin2[j]));
	if (!allPairs.empty())
	{
		flagIn = 1;
		return;
	}

	vector<int> t1, t2;
	t1.clear();
	t2.clear();
	for (int i = 0; i < pat.vn; i++)
		if (s.core1[i] == -1)
			t1.push_back(i);
	for (int i = 0; i < g.vn; i++)
		if (s.core2[i] == -1)
			t2.push_back(i);
	for (int i = 0; i < (int)t1.size(); i++)
		for (int j = 0; j < (int)t2.size(); j++)
			allPairs.push_back(make_pair(t1[i], t2[j]));
	flagAll = 1;
}

void VF2::CheckPairs(const State &s)
{
	candiPairs.clear();

	for (auto ite = allPairs.begin(); ite != allPairs.end(); ite++)
		if (check(s, ite->first, ite->second))
			candiPairs.push_back(*ite);
}

void VF2::UpdateState(State &s, int a, int b)
{
	// Update core,in,out
	for (int i = 0; i < pat.vn; i++)
	{
		s.core1[a] = b;
		s.in1[a] = 0;
		s.out1[a] = 0;
	}
	for (int i = 0; i < g.vn; i++)
	{
		s.core2[b] = a;
		s.in2[b] = 0;
		s.out2[b] = 0;
	}

	// Add new out1
	for (int i = pat.head[a]; ~i; i = pat.edge[i].next)
	{
		int v = pat.edge[i].v;
		if (s.core1[v] == -1)
			s.out1[v] = 1;
	}
	// Add new in1
	for (int i = revpat.head[a]; ~i; i = revpat.edge[i].next)
	{
		int v = revpat.edge[i].v;
		if (s.core1[v] == -1)
			s.in1[v] = 1;
	}
	// Add new out2
	for (int i = g.head[b]; ~i; i = g.edge[i].next)
	{
		int v = g.edge[i].v;
		if (s.core2[v] == -1)
			s.out2[v] = 1;
	}
	// Add new in2
	for (int i = revg.head[b]; ~i; i = revg.edge[i].next)
	{
		int v = revg.edge[i].v;
		if (s.core2[v] == -1)
			s.in2[v] = 1;
	}

	// Add to s
	s.s.push_back(make_pair(a, b));
}

bool VF2::FinalCheck(const State &s)
{
	/*puts("12312312312");
	for (auto ite = s.s.begin();ite != s.s.end();ite++)
		cout << ite->first << " " << ite->second << endl;*/
	for (int i = 0;i < pat.en;i++)
	{
		Edge e1 = pat.edge[i];
		//cout << "Edge1: " << e1.u << " " << e1.v << " " << e1.label << endl;
		bool flag = 0;
		//cout << s.core1[e1.u] << endl;
		//if (s.core1[e1.u] == -1) return 0;
		for (int j = g.head[s.core1[e1.u]];~j;j = g.edge[j].next)
		{
			Edge e2 = g.edge[j];
			//cout << "Edge2: " << e2.u << " " << e2.v << " " << e2.label << endl;
			if (e1.label == e2.label&&s.core1[e1.v]==e2.v)
			{
				flag = 1;
				break;
			}
		}
		if (!flag) return 0;
	}
	return 1;
}

bool VF2::dfs(const State &s)
{
	// Matched
	if ((int)s.s.size() == pat.vn)
	{
		if (FinalCheck(s))
		{
			//puts("Matched!");
			tlist = s.s;
			return 1;
		}
	}

	// Generate Pair(n,m)
	GenPairs(s);
	// Check allPairs, get candiPairs
	CheckPairs(s);

	// For tmp dfs store
	vector<prii> vec = candiPairs;
	vector<int> m1t, m2t;
	vector<int> tin1t, tin2t;
	vector<int> tout1t, tout2t;
	vector<int> n1t, n2t;
	vector<int> ns1t, ns2t;
	vector<int> t1t, t2t;

	//cout << vec.size() << endl;

	// Next recursive
	for (auto ite = vec.begin(); ite != vec.end(); ite++)
	{
		State ns = s;
		int a = ite->first;
		int b = ite->second;
		UpdateState(ns, a, b);

		m1t = m1, m2t = m2;
		tin1t = tin1, tin2t = tin2;
		tout1t = tout1, tout2t = tout2;
		n1t = n1, n2t = n2;
		ns1t = ns1, ns2t = ns2;
		t1t = t1, t2t = t2;

		bool ret = dfs(ns);

		m1 = m1t, m2 = m2t;
		tin1 = tin1t, tin2 = tin2t;
		tout1 = tout1t, tout2 = tout2t;
		n1 = n1t, n2 = n2t;
		ns1 = ns1t, ns2 = ns2t;
		t1 = t1t, t2 = t2t;

		if (ret) return 1;
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
	for (int i = 0; i < (int)DBGraph.size(); i++)
	{
		g = DBGraph[i];
		if (pat.vn > g.vn || pat.en > g.en) continue;
		GenRevGraph(g, revg);
		if (query()) // Matched
		{
			cout << "Matched: " << QID << " " << i << endl;
			//match.push_back(Match(tlist, i));
			ret++;
		}
	}
	return ret;
}