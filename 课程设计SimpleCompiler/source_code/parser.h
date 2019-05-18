#ifndef _PARSER_H
#define _PARSER_H
#include <bits/stdc++.h>
#include "Grammar.h"
#include "Lexer.h"
#include "SymbolTable.h"
#include "optimizequa.h"
using namespace std;

struct Action {
    int pos;
    int type = 0;
    int object;
    int tokenid;
};

struct Quat {
    int op, a, b, res;
    Quat(int op = 0, int a = 0, int b = 0, int res = 0) :
    op(op), a(a), b(b), res(res) { }
};

enum { GEQ = 1, PUSH, ASSI, IF, ELSE,
ENDIF, LAB, GOTO, WE, WH, DO };

struct Parser {
    map<pair<int, int>, int> LL1Table;
    Grammar gram;
    Lexer lex;
    vector<Token> tokens;
    stack<int> SEM;
    stack<int> SToken;
    int cnt_t = 0;        //for encode t1..t2
    vector<Quat> quats;
    Action acts[maxn];
    vector<string> acttype{"GEQ", "PUSH", "ASSI", "IF", "ELSE", "ENDIF", "LAB", "GOTO"
    "WE", "WH", "DO"};
    SymTable symtbl;


    void Get_Action();
    void Debug_LL1(stack<int>, int, int);
    void Get_LL1Table();
    void LL1();
    void GEQ(int, int);
    void PUSH(int, int);
    void ASSI();
    void IF();
    void ELSE();
    void ENDIF();
    void LAB();
    void GOTO();
    void WE();
    void WH();
    void DO();
    void Get_Quats();
    void Print_Quat(Quat);
    void Print_Act(Action);
    void Debug_Quats(stack<int>, stack<Action>, int, int);
    int Get_Type(int, int);
};

#endif // _PARSER_H
