#include <bits/stdc++.h>
#include "Complier.h"

using namespace std;

void Complier::Init_Gram() {
    gram.Get_Vn();
	gram.Get_Vt();
    gram.Get_Gram();
	gram.Get_Vnull();
    gram.Get_First();
    gram.Get_Follow();
    gram.Get_Select();

//    gram.Print_Vnull();
//    gram.Print_First();
//    gram.Print_Follow();
//    gram.Print_Select();
}

void Complier::Lexical_Analysis() {
    lex.origin = origin;
    lex.gram = gram;

    lex.Get_Tokens();

    tokens = lex.tokens;
//    puts("token:");
//    for(auto i : tokens) {
//        printf("i = %d, j = %d, id = %d\n",
//               i.i, i.j, i.Vt_id);
//        cout << gram.names[i.Vt_id] << endl;
//        cout << lex.names[lex.Table[i.i][i.j]] << endl;
//    }puts("");
}

void Complier::Grammatical_Analysis() {
    par.tokens = tokens;
    par.gram = gram;
    par.lex = lex;

    par.LL1();
}

void Complier::Init_SymTable() {
    symtbl.lines = lines;
    symtbl.lex = lex;
    symtbl.Get_SymTable();
    tokens = symtbl.lex.tokens;
}

void Complier::Get_Quats() {
    par.symtbl = symtbl;
    par.tokens = tokens;
    par.Get_Quats();

    lex = par.lex;
    quats = par.quats;
    tokens = par.tokens;
}

int Complier::get_opt_type(string op) {
    if(op == "=") return 0;
    else if(lex.keyword.count(op)) return 3;
    return 2;
}

string Complier::get_t(string str) {
    for(auto ch : str) {
        if(ch == 't') return "2";
    }
    return "1";
}

void Complier::Init_opt() {
    for(int i = 0; i < quats.size(); ++i) {
        Quat q = quats[i];
        string op = lex.names[q.op];
        string a = q.a != -1 ? lex.names[q.a] : "";
        string b = q.b != -1 ? lex.names[q.b] : "";
        string res = q.res != -1 ? lex.names[q.res] : "";
//        cout << op << a << b << res << endl;
        opt.qua[i].type = get_opt_type(op);
        opt.qua[i].op = op;
        if(a != "-") {
        opt.qua[i].num1.name = a;
        opt.qua[i].num1.type = get_t(a);
        }
        if(b != "-") {
        opt.qua[i].num2.name = b;
        opt.qua[i].num2.type = get_t(b);
        }
        if(res != "-") {
        opt.qua[i].ans.name = res;
        opt.qua[i].ans.type = get_t(res);
        }
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    Complier c;
    c.Init_Gram();
    c.par.Get_Action();
    string str;
    int line = 1;
//    while(getline(cin, str)) {
//        if(str.size() == 0) continue;
//        c.lines.push_back(str);
//        printf("line %d: ", line++);
//        cout << str << endl;
//        c.origin += str + " ";
//    }
    c.zyq.lexical_analysis(c.lines,c.origin);
//    puts("origin");
//    cout << c.origin << endl;
    c.Lexical_Analysis();
    c.Grammatical_Analysis();
    c.Init_SymTable();
    c.Get_Quats();
    c.symtbl.Print_RegularTable();
    c.Init_opt();
    c.opt.run();
    return 0;
}


















