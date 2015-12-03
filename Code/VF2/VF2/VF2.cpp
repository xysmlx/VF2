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
        ns1.push_back(i);
    for (int i = 0; i < g.vn; i++)
        ns2.push_back(i);

    set_union(tin1.begin(), tin1.end(), tout1.begin(), tout1.end(), t1.begin());
    set_union(tin1.begin(), tin1.end(), tout2.begin(), tout2.end(), t2.begin());

    vector<int> tmp(Graph::maxv);

    sort(n1.begin(), n1.end());
    sort(n2.begin(), n2.end());
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
    tmp = ;

    // Sort
    sort(pred1.begin(), pred1.end());
    sort(pred2.begin(), pred2.end());
    sort(succ1.begin(), succ1, end());
    sort(succ2.begin(), succ2.end());
}

bool VF2::check(const State &s, int a, int b)
{
    CalVec(s, a, b);

    if (CheckPrev(s, a, b) && CheckSucc(s, a, b) && CheckIn(s, a, b) && CheckOut(s, a, b) && CheckNew(s, a, b))
        return 1;
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
    for (auto ite = candiPairs.begin(); ite != candiPairs.end(); ite++)
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
    for (int i = 0; i < (int)DBGraph.size(); i++)
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