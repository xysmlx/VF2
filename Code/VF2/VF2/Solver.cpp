#include "Solver.h"

void Solver::init()
{
	queryPath.clear();
	DBGraph.clear();
	QueryGraph.clear();
	outputPath.clear();
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
			tmp.adde(p, q, l);
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
	// Standard data set
	dbPath = "Data/mygraphdb.data";
	queryPath.push_back("Data/Q4.my");
	queryPath.push_back("Data/Q8.my");
	queryPath.push_back("Data/Q12.my");
	queryPath.push_back("Data/Q16.my");
	queryPath.push_back("Data/Q20.my");
	queryPath.push_back("Data/Q24.my");

	// Test data set
	/*dbPath = "db.txt";
	queryPath.push_back("query.txt");*/

	// Output path: ./Output/ans_.txt
	_rmdir("Output");
	_mkdir("Output");
	string tt = "Output/ans";
	for (int i = 0;i < (int)queryPath.size();i++)
		outputPath.push_back(tt + (char)(i + '1') + ".txt");
	ofstream fout;
	for (int i = 0;i < (int)outputPath.size();i++)
	{
		fout.open(outputPath[i].c_str());
		fout.close();
	}

	ReadDB(dbPath);

	puts("Read Data Finished!");
}

void Solver::PrintQueryAns(int id, int cnt)
{
	ofstream fout;
	fout.open(outputPath[id].c_str(), ios::app);

	fout << "+++++" << endl;
	fout << "Query ID: " << vf2.QueryID << endl;
	fout << "Count: " << vf2.match.size() << endl;

	// Not output match details
	for (int i = 0;i < (int)vf2.match.size();i++)
		fout << "Mathch: " << vf2.QueryID << " " << vf2.match[i].id << endl;

	// Output match details
	//for (int i = 0;i < (int)vf2.match.size();i++)
	//{
	//	fout << "-----" << endl;
	//	fout << "Graph ID: " << vf2.match[i].id << endl;
	//	fout << "pat" << "\t" << "g" << endl;
	//	// Not output match details
	//	/*for (int j = 0;j < (int)vf2.match[i].s.size();j++)
	//		fout << vf2.match[i].s[i].first << "\t" << vf2.match[i].s[i].second << endl;*/
	//	fout << "-----" << endl;
	//}

	fout << "+++++" << endl;

	fout << endl;

	fout.close();
}

void Solver::solve()
{
	vf2.init(DBGraph);
	for (int _ = 0;_ < (int)queryPath.size();_++)
	{
		ReadQuery(queryPath[_]);
		for (int i = 0;i < (int)QueryGraph.size();i++)
		{
			int cnt = vf2.vf2(QueryGraph[i], i);
			PrintQueryAns(_, cnt);
		}
	}
}

void Solver::output()
{
	//
}