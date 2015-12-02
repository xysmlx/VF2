#ifndef GRAPH_H
#define GRAPH_H

#include "head.h"

struct Vertex
{
	int id;
	int label;
	int seq;
	bool del;

	Vertex(int _id = 0, int _label = 0) : id(_id), label(_label), seq(-1), del(0) {}
	~Vertex() {}
};

struct Edge
{
	int u;
	int v;
	int label;
	int next;
	bool del;

	Edge(int _u = 0, int _v = 0, int _label = 0, int _next = -1) : u(_u), v(_v), label(_label), next(_next), del(0) {}
	~Edge() {}

	bool operator == (const Edge &o) const
	{
		return u == o.u&&v == o.v&&label == o.label;
	}
};

class Graph
{
public:
	Graph()
	{
		memset(head, -1, sizeof(head));
		vn = 0;
		en = 0;
	}
	~Graph() {}

	void init();
	void addv(int id, int label);
	void addse(int u, int v, int label);
	void adde(int u, int v, int label);
	void delse(int u, int v, int label);
	void dele(int u, int v, int label);

public:
	const static int maxv = 250;
	const static int maxe = 510;

public:
	int head[maxv];
	int vn;
	int en;
	Vertex vtx[maxv]; // 0 to vn-1
	Edge edge[maxe]; // 0 to en-1
};

#endif