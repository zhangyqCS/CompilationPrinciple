#include <bits/stdc++.h>
#include "Parser.h"

using namespace std;

void Parser::Get_LL1Table() {
    //puts("Yes");
    for(auto i : gram.Select) {
        pair<int, vector<int>> p = gram.Gram[i.fi];
        //p : product A -> ab
        for(auto j : i.se) {
            LL1Table[{p.fi, j}] = i.fi;
//            printf("(%s, %s) = %d\n", gram.names[p.fi].c_str(),
//            gram.names[j].c_str(), i.fi);
        }
    }
}

void Parser::Debug_LL1(stack<int> S, int j, int d) {
    vector<int> v;
    while(S.size()) {
        v.pb(S.top());
        S.pop();
    }
    reverse(v.begin(), v.end());
    printf("sta: ");
    for(auto x : v) {
        printf(" %s", gram.names[x].c_str());
    }cout << endl;
    int r = tokens[d].i, c = tokens[d].j;
    printf("%s", lex.names[lex.Table[r][c]].c_str());
    cout << endl;
}

void Parser::LL1() {
    Get_LL1Table();
    stack<int> S;
    S.push(gram.Start);
    int d = 0;
//    printf("Start: %s\n", gram.names[gram.Start].c_str());
    while(!S.empty()) {
//        printf("sz = %d\n", S.size());
        int i = S.top(), j = tokens[d].Vt_id;
//        Debug_LL1(S, j, d);
        if(gram.Vt.count(i)) {
            if(S.top() == j) {
                d++;
                S.pop();
            }
            else {
                puts("Not Match!");
                exit(0);
            }
        }
        else if(gram.Vn.count(i)) {
            S.pop();
//            puts("yes");
            if(LL1Table.count({i, j})) {
                //puts("yes");
                vector<int> rev;
                for(auto x : gram.Gram[LL1Table[{i, j}]].se) {
//                    printf("%s", gram.names[x].c_str());
                    if(gram.names[x] == "~") continue;
                    rev.pb(x);
                }
//                cout << endl;
                reverse(rev.begin(), rev.end());
                for(auto x : rev) S.push(x);
            }
            else {
                puts("Don't have LL1Table !");
                exit(0);
            }
        }
    }
    puts("exp is right!");
}

void Parser::Print_Quat(Quat q) {
    string op, a, b, res;
    op = lex.names[q.op];
    if(q.a == -1) a = "_";
    else a = lex.names[q.a];
    if(q.b == -1) b = "_";
    else b = lex.names[q.b];
    if(q.res == -1) res = "_";
    else res = lex.names[q.res];
    printf("(%s, %s, %s, %s)\n", op.c_str(),
    a.c_str(), b.c_str(), res.c_str());
}

int Parser::Get_Type(int id, int tid) {
    if(tokens[tid].type != -1) return tokens[tid].type;
//    printf("level = %d\n", tokens[tid].level);
    vector<Record> vr = symtbl.Infos[tokens[tid].level][id];
    return tokens[tid].type = vr.back().type;
}

void Parser::GEQ(int op, int tokenid) {

    int tr = SToken.top(); SToken.pop();
    int tl = SToken.top(); SToken.pop();
    int rop = SEM.top(); SEM.pop();
    int lop = SEM.top(); SEM.pop();
//    printf("level = %d\n", tokens[tl].level);
    int typer = Get_Type(lop, tl), typel = Get_Type(rop, tr);
    if(typer != typel) {
        printf("Error(%d): Type not match : (%s, %s)!\n",
        tokens[tl].level+1, lex.names[lop].c_str(), lex.names[rop].c_str());
        exit(0);
    }
    string t = "t";
    char num[10];
    sprintf(num, "%d", cnt_t);
    t += num;
    ++cnt_t;
    quats.push_back(Quat(op, lop, rop, lex.Get_Id(t)));
    SEM.push(lex.Get_Id(t));
    Token tt;
    tt.level = tokens[tl].level;
    tt.Vt_id = tokens[tl].Vt_id;
    tt.type = tokens[tl].type;
    tt.i = -1;
//    tt.type = typel;
    tokens.push_back(tt);
    SToken.push(tokens.size()-1);
    Print_Quat(quats.back());
}

void Parser::PUSH(int x, int tokenid) {
    SEM.push(x);
    SToken.push(tokenid);
}

void Parser::Get_Action() {
    int cnt;
    cin >> cnt;
    for(int i = 0; i < cnt; ++i) {
        int idx, type, pos;
        cin >> idx >> type >> pos;
        --idx;
        acts[idx].type = type;
        acts[idx].pos = pos;
//        printf("idx = %d, type = %d, pos = %d\n", idx, type, pos);
    }
}

void Parser::Debug_Quats(stack<int> S, stack<Action> SACT, int j, int d) {
    vector<int> v;
    while(S.size()) {
        v.pb(S.top());
        S.pop();
    }
    reverse(v.begin(), v.end());
    printf("S: ");
    for(auto x : v) {
        if(x == -1) printf(" -1");
        else printf(" %s", gram.names[x].c_str());
    }cout << endl;
    int r = tokens[d].i, c = tokens[d].j;
    printf("%s", lex.names[lex.Table[r][c]].c_str());
    cout << endl;
}

void Parser::ASSI() {
    int lop = SEM.top(); SEM.pop();
    int res = SEM.top(); SEM.pop();
    quats.push_back(Quat(lex.Get_Id("="), lop, -1, res));
    Print_Quat(quats.back());
}

void Parser::IF() {
    int lop = SEM.top(); SEM.pop();
    quats.push_back(Quat(lex.Get_Id("if"), lop, -1, -1));
    Print_Quat(quats.back());
}

void Parser::ELSE() {
    quats.push_back(Quat(lex.Get_Id("el"), -1, -1, -1));
    Print_Quat(quats.back());
}

void Parser::ENDIF() {
    quats.push_back(Quat(lex.Get_Id("ie"), -1, -1, -1));
    Print_Quat(quats.back());
}

void Parser::LAB() {
    int res = SEM.top(); SEM.pop();
    quats.push_back(Quat(lex.Get_Id("lb"), -1, -1, res));
    SEM.push(res);
    Print_Quat(quats.back());
}

void Parser::GOTO() {
    int res = SEM.top(); SEM.pop();
    quats.push_back(Quat(lex.Get_Id("gt"), -1, -1, res));
    Print_Quat(quats.back());
}

void Parser::WE() {
    quats.push_back(Quat(lex.Get_Id("we"), -1, -1, -1));
    Print_Quat(quats.back());
}

void Parser::WH() {
    quats.push_back(Quat(lex.Get_Id("wh"), -1, -1, -1));
    Print_Quat(quats.back());
}

void Parser::DO() {
    int lop = SEM.top(); SEM.pop();
    quats.push_back(Quat(lex.Get_Id("do"), lop, -1, -1));
    Print_Quat(quats.back());
}

void Parser::Print_Act(Action a) {
    printf("obj = %d, pos = %d, type = %d\n", a.object, a.pos, a.type);
}

void Parser::Get_Quats() {
    stack<int> S;
    stack<Action> SACT;
    S.push(gram.Start);
    int d = 0;
    while(!S.empty()) {
        int i = S.top(), j = tokens[d].Vt_id;
//        printf("level = %d\n", tokens[d].level);
//        Debug_Quats(S, SACT, j, d);
        if(i == -1) {   //action is the top
            S.pop();
            if(SACT.empty()) { puts("SACT is null!"); exit(0); }
            Action act = SACT.top(); SACT.pop();
//            printf("act = %s\n", acttype[act.type-1].c_str());
//            printf("act = %d\n", act.type);
            if(act.type == 1) {     //GEQ
                GEQ(act.object, act.tokenid);
            }
            else if(act.type == 2) {
                PUSH(act.object, act.tokenid);
            }
            else if(act.type == 3) {
                ASSI();
            }
            else if(act.type == 4) {
                IF();
            }
            else if(act.type == 5) {
                ELSE();
            }
            else if(act.type == 6) {
                ENDIF();
            }
            else if(act.type == 7) {
                LAB();
            }
            else if(act.type == 8) {
                GOTO();
            }
            else if(act.type == 9) {
                WE();
            }
            else if(act.type == 10) {
                WH();
            }
            else if(act.type == 11) {
                DO();
            }
        }
        else if(gram.Vt.count(i)) {
            if(S.top() == j) {
                d++;
                S.pop();
            }
        }
        else if(gram.Vn.count(i)) {
            S.pop();
            if(LL1Table.count({i, j})) {
                vector<int> rev;
                int k = 0;      //count the position
                int t = LL1Table[{i, j}];   //the index of product
                for(auto x : gram.Gram[t].se) {
                    if(gram.names[x] == "~") continue;
                    rev.pb(x);
                    if(acts[t].type == 0) continue;
                    if(k == acts[t].pos) {
                        rev.pb(-1);
                        int r = tokens[d].i, c = tokens[d].j;
                        acts[t].object = lex.Table[r][c];
                        acts[t].tokenid = d;
//                        Print_Act(acts[t]);
//                        printf("t = %d\n", t);
                        SACT.push(acts[t]);
                    }
                    ++k;
                }
                reverse(rev.begin(), rev.end());
                for(auto x : rev) S.push(x);
            }
        }
    }
}













