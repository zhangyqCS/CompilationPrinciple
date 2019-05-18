#ifndef _LEXER_H
#define _LEXER_H
#include <bits/stdc++.h>
#include "Grammar.h"

using namespace std;

struct Token {
    int i;
    int j;
    int Vt_id;
    int level;
    int type = -1;
    Token(int a = 0, int b = 0, int c = 0) {
        i = a, j = b, Vt_id = c;
    }
};

struct Lexer {
    string origin;
    Grammar gram;
    vector<string> names;
    vector<int> Table[6];
    vector<Token> tokens;
    set<string> keyword{"int", "double", "char", "if", "else", "goto", "while", "double"};
    set<string> bound{",", ":", ";", "=", "+", "-", "{", "}",
    "*", "/", "(", ")", "#", ">", "<", "==", ">=", "<=", "!="};
    set<string> iden;
    int Get_Id(string);
    int Get_pos(int, int);
    void Get_Tokens();
};
#endif // _LEXER_H
