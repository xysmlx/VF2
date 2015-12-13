#include "Solver.h"

Solver solver;

void init()
{
	// 0: no output matching ans, 1: output matching ans
	solver.init(0);
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
	//freopen("debug.txt", "w", stdout);
	init();
	input();
	solve();
	output();
}