#include <bits/stdc++.h>
#include "Grammar.h"
using namespace std;

void Grammar::Print_Vnull() {
    puts("Vnull:");
	for(auto i : Vnull) {
        cout << names[i] << endl;
	}cout << endl;
}

void Grammar::Print_First() {
    puts("First:");
    for(auto i : First) {
        printf("%s :", names[i.fi].c_str());
        for(auto j : i.se) {
            cout << " " << names[j];
        }
        cout << endl;
    }cout << endl;
}

void Grammar::Print_Follow() {
    puts("Follow:");
    for(auto i : Follow) {
        printf("%s :", names[i.fi].c_str());
        for(auto j : i.se) {
            cout << " " << names[j];
        }
        cout << endl;
    }cout << endl;
}

void Grammar::Print_Select() {
    puts("Select:");
    for(auto i : Select) {
        pair<int, vector<int>> p = Gram[i.fi];
        printf("%s :", names[p.fi].c_str());
		for(auto x : p.se) {
            printf(" %s", names[x].c_str());
		}
		//cout << endl;
		cout << " [";
        for(auto j : i.se) {
            cout << " " << names[j];
        }
        cout << " ]" << endl;
    }cout << endl;
}

int Grammar::Id(string str) {
	for(int i = 0; i < names.size(); ++i) {
        if(names[i] == str) {
            return i;
        }
    }
    names.push_back(str);
    return names.size() - 1;
}

void Grammar::Get_Set(set<int> &Set) {
	int cnt;
	cin >> cnt;
	for(int i = 0; i < cnt; ++i) {
		string str;
		cin >> str;
		Set.insert(Id(str));
		if(Start == -1) Start = Id(str);
//		cout << names[Id(str)] << endl;
	}
//	cout << endl;
}

void Grammar::Get_Vn() {
	Get_Set(Vn);
}

void Grammar::Get_Vt() {
	Get_Set(Vt);
}

void Grammar::Get_Gram() {
	int cnt;
	cin >> cnt;
	for(int i = 0; i < cnt; ++i) {
		string str;
		int L, cnt2;
		cin >> str >> cnt2;
		L = Id(str);
		vector<int> R;
		for(int j = 0; j < cnt2; ++j) {
            cin >> str;
            R.pb(Id(str));
		}
		Gram.push_back({L, R});
//		printf("%s :", names[L].c_str());
//		for(auto x : R) {
//            printf(" %s", names[x].c_str());
//		}
//		cout << endl;
	}
}

bool Grammar::Check_Vnull(vector<int> &R) {
	for(auto i : R) {
		if(!Vnull.count(i)) return false;
	}
	return true;
}

void Grammar::Get_Vnull() {
	bool changing = true;
	while(changing) {
		changing = false;
		for(auto p : Gram) {
			vector<int> R = p.se;
			if(names[R[0]] == "~" && !Vnull.count(p.fi)) {
				Vnull.insert(p.fi);
				changing = true;
			}
			else if(Check_Vnull(R) && !Vnull.count(p.fi)) {
				Vnull.insert(p.fi);
				changing = true;
			}
		}
	}
}

void Grammar::Get_First() {
    bool changing = true;
    while(changing) {
//        Print_First();
        changing = false;
        for(auto p : Gram) {
            vector<int> R = p.se;
            for(auto i : R) {
                if(Vt.count(i)) {
                    if(!First[p.fi].count(i)) {
                        First[p.fi].insert(i);
                        changing = true;
                    }
                    break;
                }
                else if(Vn.count(i)) {
                    for(auto vt : First[i]) {
                        if(!First[p.fi].count(vt)) {
                            changing = true;
                            First[p.fi].insert(vt);
                        }
                    }
                    if(!Vnull.count(i)) break;
                }
            }
        }
    }
}

void Grammar::Get_Follow() {
    bool changing = true;
    while(changing) {
        changing = false;
        for(auto p : Gram) {
            set<int> temp_f = Follow[p.fi];
            vector<int> R = p.se;
            reverse(R.begin(), R.end());
            for(auto i : R) {
                if(Vt.count(i)) {
                    temp_f.clear();
                    temp_f.insert(i);
                }
                else if(Vn.count(i)) {
                    for(auto vt : temp_f) {
                        if(!Follow[i].count(vt)) {
                            changing = true;
                            Follow[i].insert(vt);
                        }
                    }
                    if(!Vnull.count(i)) temp_f = First[i];
                    else {
                        for(auto vt : First[i]) {
                            temp_f.insert(vt);
                        }
                    }
                }
            }
        }
    }
//    Print_Follow();
}

void Grammar::Calc_Select(int i) {
    pair<int, vector<int>> p = Gram[i];
    vector<int> R = p.se;
    for(auto j : R) {
        if(Vt.count(j)) {
            Select[i].insert(j);
            return;
        }
        else if(Vn.count(j)) {
            for(auto f : First[j]) {
                Select[i].insert(f);
            }
            if(!Vnull.count(j)) return;
        }
    }
    for(auto f : Follow[p.fi]) {
        Select[i].insert(f);
    }
}

void Grammar::Get_Select() {
    for(int i = 0; i < Gram.size(); ++i) {
        Calc_Select(i);
    }
}


















