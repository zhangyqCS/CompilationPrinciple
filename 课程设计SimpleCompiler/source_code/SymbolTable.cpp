#include <bits/stdc++.h>
#include "SymbolTable.h"

using namespace std;

void SymTable::Get_NewRecord(string type, int range, vector<Record> &S, int line, int name) {
    Record rcd;
    rcd.range = range;
    if(type == "int") {
        rcd.type = INT;
    }
    else if(type == "double") {
        rcd.type = DOUBLE;
    }
    else if(type == "bool") {
        rcd.type = BOOL;
    }
    else if(type == "char") {
        rcd.type = CHAR;
    }
    rcd.line = line;
    rcd.name = name;
    S.push_back(rcd);
    synbl.push_back(rcd);
}

void SymTable::Pop_Record(int range, map<int, vector<Record>> &InfoTable) {
    for(auto &p : InfoTable) {
        vector<Record> &S = p.second;
        if(S.size()) {
            if(S.back().range == range) S.pop_back();
        }
    }
}

void SymTable::Print_Table(map<int, vector<Record>> InfoTable) {
    for(auto p : InfoTable) {
        printf("%s : \n", lex.names[p.first].c_str());
        vector<Record> S = p.second;
        reverse(S.begin(), S.end());
        for(auto i : S) {
            printf("type = %d, range = %d, line = %d\n", i.type, i.range, i.line);
        }
    }cout << endl;
}

bool IsArr(string str, string &name, int &num) {
    bool ok = false;
    string x;
    for(int i = 0; i < str.size(); ++i) {
        if(!ok) name.push_back(str[i]);
        if(str[i] == '[') {
            ok = true;
        }
        else if(str[i] == ']') break;
        else if(ok) {
            x.push_back(str[i]);
        }
    }
    name.pop_back();
    sscanf(x.c_str(), "%d", &num);
    return ok;
}

int get_type(string s) {
    if(s == "int") return INT;
    else if(s == "double") return DOUBLE;
    else if(s == "char") return CHAR;
    else if(s == "bool") return BOOL;
}

int get_size(int i) {
    if(i == 3) return 1;
    if(i == 1) return 8;
    return 4;
}

void SymTable::Print_RegularTable() {
    puts("SYNBL");
    printf("%-8s%-8s%-8s%-8s\n", "NAME", "TYP", "CAT", "ADDR");
    int d = 0; //   the address
    for(int i = 0; i < synbl.size(); ++i) {
        Record r = synbl[i];
//        cout << lex.names[r.name] << endl;
        printf("%-8s", lex.names[r.name].c_str());
        if(r.type == 0) {
            printf("%-8s", "int");
        }
        else if(r.type == 1) {
            printf("%-8s", "double");
        }
        else if(r.type == 2) {
            printf("%-8s", "char");
        }
        else if(r.type == 3) {
            printf("%-8s", "bool");
        }
        else if(r.type == 4) {
            printf("%-8s", "AINFL");
        }
        else if(r.type == 5) {
            printf("%-8s", "PFINFL");
        }
        if(r.type == 0) {
            printf("%-8s", "v");
        }
        else if(r.type == 1) {
            printf("%-8s", "v");
        }
        else if(r.type == 2) {
            printf("%-8s", "v");
        }
        else if(r.type == 3) {
            printf("%-8s", "v");
        }
        else if(r.type == 4) {
            printf("%-8s", "t");
        }
        else if(r.type == 5) {
            printf("%-8s", "f");
        }
        if(0 <= r.type && r.type < 4) {
            char addr[10];
            sprintf(addr, "(%d,%d)", r.range, d);
            d += get_size(r.type);
            printf("%-8s\n", addr);
        }
        else if(r.type == 4) {
            printf("%-8s\n", "AINFL, 1");
            r.low = d, r.up = d + r.clen;
            d += r.clen;
            arr.push_back(r);
        }
        else if(r.type == 5) {
            printf("%-8s\n", "PFINFL");
        }
    }

    cout << endl;
    //Type Table
    puts("TYPEL");
    printf("%-8s%-8s\n", "NAME", "TYP");
    for(auto r : arr) {
        printf("%-8s", lex.names[r.name].c_str());
        printf("%-8s\n", "AINFL");
    }
    cout << endl;
    puts("AINFL");
    printf("%-8s%-8s%-8s%-8s%-8s\n", "NAME", "LOW", "UP", "CTP", "CLEN");
    for(auto r : arr) {
        printf("%-8s", lex.names[r.name].c_str());
        printf("%-8d", r.low);
        printf("%-8d", r.up);
//        printf("%-8d", r.ctp);
        if(r.ctp == 0) {
            printf("%-8s", "int");
        }
        else if(r.ctp == 1) {
            printf("%-8s", "double");
        }
        else if(r.ctp == 2) {
            printf("%-8s", "char");
        }
        else if(r.ctp == 3) {
            printf("%-8s", "bool");
        }
        printf("%-8d", r.clen);
    }
    cout << endl;
    cout << endl;
    puts("PFINFL");
    printf("%-8s%-8s%-8s%-8s%-8s\n", "LEVEL", "OFF", "FN", "ENTYR", "PARAM");
    printf("%-8s%-8s%-8s%-8s%-8s\n", "0", "0", "0", "0", "0");
    cout << endl;
}

void SymTable::Get_SymTable() {
    map<int, vector<Record>> CurTable;
    int range = 0;        //count level;
    int d = 0;
    //Infos.push_back(CurTable);
    for(int i = 0; i < lines.size(); ++i) {
//        cout << lines[i] << endl;
        Infos.push_back(CurTable);
        string str = lines[i];
        vector<string> vs;
        stringstream ss(str);
        while(ss >> str) vs.push_back(str);
        for(int j = 0; j < vs.size(); ++j, ++d) {
            lex.tokens[d].level = i;
        }
//        printf("line = %d\n", i);
//        Print_Table(CurTable);
        if(i == 0) {
            vector<Record> &S = CurTable[lex.Get_Id("main")];
            Record funrec;
            funrec.range = 0;
            funrec.Init_Fun(0, 0, 0, 0);
            funrec.name = lex.Get_Id("main");
            S.push_back(funrec);
            synbl.push_back(funrec);
//            cout << lex.names[synbl.back().name] << endl;
        }
        else if(Def.count(vs[0])) {      // define
            for(int j = 1; j < vs.size(); ++j) {
                string name;
                int num;
                if(IsArr(vs[j], name, num)) {
                    vector<Record> &S = CurTable[lex.Get_Id(name)];
                    Record arrrec;
                    arrrec.ctp = get_type(vs[j]);
                    arrrec.line = i;
                    arrrec.range = range;
                    arrrec.Init_Arr(0, num, get_type(vs[0]), num*get_size(get_type(vs[0])));
                    arrrec.name = lex.Get_Id(name);
                    S.push_back(arrrec);
                    synbl.push_back(arrrec);
                    continue;
                }
                if(vs[j] == "," || vs[j] == ";") continue;
                if(lex.keyword.count(vs[j]) || lex.bound.count(vs[j])) continue;
                vector<Record> &S = CurTable[lex.Get_Id(vs[j])];
                if(S.empty()) {
                    Get_NewRecord(vs[0], range, S, i + 1, lex.Get_Id(vs[j]));
//                    printf("%s\n", vs[0].c_str());
                }
                else {
                    Record rcd = S.back();
                    if(rcd.range == range) {
                        printf("Error(%d): redefine! Last define is at line : (%d) !\n", i + 1, rcd.line);
                        exit(0);
                    }
                    else {
                        Get_NewRecord(vs[0], range, S, i + 1, lex.Get_Id(vs[j]));
                    }
                }
            }
        }
        else if(vs[0] == "{") {         //get into new range
            ++range;
        }
        else if(vs[0] == "}") {         //get out of a range
            Pop_Record(range, CurTable);
        }
        else {                          //use of a var
            for(int j = 0; j < vs.size(); ++j) {
                if(lex.iden.count(vs[j])) {
                    vector<Record> vr = CurTable[lex.Get_Id(vs[j])];
                    if(vr.empty()) {
                        printf("Error(%d): Not define %s !\n", i + 1, vs[j].c_str());
                        exit(0);
                    }
                }
            }
        }
    }
}















