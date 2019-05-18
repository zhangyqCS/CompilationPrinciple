#include <bits/stdc++.h>
#include "Grammar.h"
#include "Lexer.h"
#include "parser.h"
#include "SymbolTable.h"
#include "optimizequa.h"
#include "lexical.h"
#include "Target.h"

using namespace std;

struct Complier {
    Grammar gram;
    string origin;
    Lexer lex;
    vector<Token> tokens;
    Parser par;
    vector<Quat> quats;
    SymTable symtbl;
    vector<string> lines;
    Opt opt;
    ZYQ zyq;
    Target tar;

    int get_opt_type(string op);
    string get_t(string str);
    void Init_Gram();
    void Lexical_Analysis();
    void Grammatical_Analysis();
    void Init_SymTable();
    void Get_Quats();
    void Init_opt();
    void Init_target();
};
