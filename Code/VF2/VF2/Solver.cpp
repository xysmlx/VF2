#include "Solver.h"

void Solver::init()
{
	vf2.init();
	queryPath.clear();
	DBGraph.clear();
	QueryGraph.clear();
}

void Solver::ReadFile(string path, vector<Graph> &vec)
{
	vec.clear();

	ifstream fin;
	fin.open(path.c_str());

	Graph tmp;
	string buff;
	int n;
	int m, l;
	int p, q;
	while (getline(fin, buff))
	{
		//cout << buff << endl;
		//getchar();
		if (buff.size() == 0) continue;
		if (buff == "t # -1")
		{
			if (n == 0) continue;
			vec.push_back(tmp);
			break;
		}
		if (buff[0] == 't')
		{
			sscanf(buff.c_str(), "t # %d", &n);
			if (n == 0) continue;
			vec.push_back(tmp);
			tmp.init();
		}
		else if (buff[0] == 'v')
		{
			sscanf(buff.c_str(), "v %d %d", &m, &l);
			tmp.addv(m, l);
		}
		else if (buff[0] == 'e')
		{
			sscanf(buff.c_str(), "e %d %d %d", &p, &q, &l);
			tmp.addse(p, q, l);
		}
		else puts("Error!");
	}

	//cout << vec.size() << endl;

	fin.close();
}

void Solver::ReadDB(string path)
{
	ReadFile(path, DBGraph);
}

void Solver::ReadQuery(string path)
{
	ReadFile(path, QueryGraph);
}

void Solver::input()
{
	dbPath = "Data/mygraphdb.data";
	queryPath.push_back("Data/Q4.my");
	queryPath.push_back("Data/Q8.my");
	queryPath.push_back("Data/Q12.my");
	queryPath.push_back("Data/Q16.my");
	queryPath.push_back("Data/Q20.my");
	queryPath.push_back("Data/Q24.my");

	ReadDB(dbPath);
	vf2.graph = DBGraph;
}

void Solver::solve()
{
	for (int _ = 0;_ < (int)queryPath.size();_++)
	{
		ReadQuery(queryPath[_]);
		for (int i = 0;i < (int)QueryGraph.size();i++)
		{
			vf2.query = QueryGraph[i];
			//Cal
		}
	}
}

void Solver::output()
{
	//
}