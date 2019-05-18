#ifndef _GRAMMAR_H
#define _GRAMMAR_H
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
using namespace std;

struct Grammar {
	vector<string> names;
	set<int> Vt, Vn;
	int Start = -1;
	vector<pair<int, vector<int>>> Gram;
	set<int> Vnull;
	map<int, set<int>> First;
	map<int, set<int>> Follow;
	map<int, set<int>> Select;

	int Id(string str);
	void Get_Set(set<int> &);
	void Get_Vn();
	void Get_Vt();
	void Get_Gram();
	void Get_Vnull();
	bool Check_Vnull(vector<int> &);
	void Get_First();
	void Get_Follow();
	void Calc_Select(int);
	void Get_Select();
	void Print_Follow();
	void Print_First();
	void Print_Select();
	void Print_Vnull();
};

#endif
