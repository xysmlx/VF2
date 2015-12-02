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
	init();
	input();
	solve();
	output();
}