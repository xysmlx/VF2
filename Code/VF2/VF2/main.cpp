#include "Solver.h"

Solver solver;

void init()
{
	solver.init();
}

void input()
{
	solver.input();
}

void solve()
{
	solver.solve();
}

void output()
{
	solver.output();
}

int main()
{
	freopen("debug.txt", "w", stdout);
	init();
	input();
	solve();
	output();
}