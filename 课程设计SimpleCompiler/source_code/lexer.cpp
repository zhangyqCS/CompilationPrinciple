#include <bits/stdc++.h>
#include "Lexer.h"

using namespace std;

int Lexer::Get_Id(string str) {     //hash for the string (differ from product)
    for(int i = 0; i < names.size(); ++i) {
        if(names[i] == str) {
            return i;
        }
    }
    names.push_back(str);
    return names.size() - 1;
}

int Lexer::Get_pos(int i, int id) {         //put into table and return the y
    for(int j = 0; j < Table[i].size(); ++j) {
        if(Table[i][j] == id) {
            return j;
        }
    }
    Table[i].push_back(id);
    return Table[i].size() - 1;
}

void Lexer::Get_Tokens() {
//    puts("Lexer:");
    stringstream ss(origin);
    string str;
    while(ss >> str) {
//        cout << str << endl;
        if(isdigit(str[0])) {       //0 means constant number
            tokens.push_back(Token(0,
            Get_pos(0, Get_Id(str)), gram.Id("Num")));
        }
        else if(keyword.count(str)){
            tokens.push_back(Token(1,
            Get_pos(1, Get_Id(str)), gram.Id(str)));
//            printf("Id = %d, %d\n", gram.Id(str),
//            tokens.back().Vt_id);
        }
        else if(bound.count(str)) {
            tokens.push_back(Token(2,
            Get_pos(2, Get_Id(str)), gram.Id(str)));
        }
        else {
            tokens.push_back(Token(3,
            Get_pos(3, Get_Id(str)), gram.Id("Iden")));
            iden.insert(str);
//            cout << str << endl;
        }
    }
}










