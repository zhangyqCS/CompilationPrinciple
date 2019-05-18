#ifndef _target_H
#define _target_H
#include "optimizequa.h"
#include<cstdio>
#include<vector>
#include<cstdlib>
#include<algorithm>
#include<string>
#include<stack>
#include<iostream>
#include<utility>
#include<map>
#include<set>
#include<iomanip>

struct Target {

struct Token
{
	string name;
	string type; //1-非临时变量，2-临时变量，3-数字
	Token(string a="",string b="")
	{
		name = a; type = b;
	}
};

struct ACT_INF //四元式的活跃信息
{
	string num1;
	string num2;
	string ans;
	ACT_INF(string a="", string b="", string c="")
	{
		num1 = a; num2 = b; ans = c;
	}
};

struct ACT_SYNBL
{
	string name;
	string act_inf;
	ACT_SYNBL(string a="", string b="")
	{
		name = a; act_inf = b;
	}
};

struct Quaternion
{
	int block; //所属快的标识
	int type; //类型，0-赋值语句 2-双操作数 3-if,else,wh...
	string op; //操作
	Token num1; //操作数1
	Token num2; //操作数2
	Token ans; //结果
	Quaternion(int a,int b, string c, Token d, Token e, Token f)
	{
		block = a; type = b; op = c; num1 = d; num2 = e; ans = f;
	}
};

set<string>Tmp_var; //临时变量
set<string>var; //非临时变量
vector< vector<ACT_INF> >Act_inf;
vector< vector<Quaternion> > qua;
vector< vector<ACT_SYNBL> >Act_synbl;
vector<string>objcode;
stack<string>SEM; //保存待返填地址

void init()
{
	/*ector<Quaternion>tmp1,tmp2,tmp3;
	Token token1("a", "1"); Token token2("b", "1"); Token token3("t1", "2");
	Quaternion quaternion1(0,2, ">", token1, token2, token3); //(>,a,b,t1)
	tmp1.push_back(quaternion1);

	Token token4; Token token5;
	Quaternion quaternion2(0,2, "if", token3, token4, token5);
	tmp1.push_back(quaternion2); //(if,t1,_,_)

	Token token6("t2", "2");
	Quaternion quaternion3(1,2, "+", token1, token2, token6);
	tmp2.push_back(quaternion3); //(+,a,b,t2)

	Token token7("c", "1"); Token token8("x", "1");
	Quaternion quaternion4(1,2, "*", token6, token7, token8);
	tmp2.push_back(quaternion4); //(*,t2,c,x)

	Token token9;
	Quaternion quaternion5(1,2, "el", token9, token4, token5);
	tmp2.push_back(quaternion5); //(el,_,_,_)

	Token token10("t3", "2");
	Quaternion quaternion6(2,2, "*", token1, token2, token10);
	tmp3.push_back(quaternion6); //(*,a,b,t3)

	Token token11("5", "3");
	Quaternion quaternion7(2, 2, "-", token11, token10, token8);
	tmp3.push_back(quaternion7); //(-,5,t3,x)

	Quaternion quaternion8(2, 2, "ie", token9, token4, token5);
	tmp3.push_back(quaternion8); //(ie,_,_,_)
	*/

	//初始化临时变量表
	//Tmp_var.insert("t1"); Tmp_var.insert("t2"); Tmp_var.insert("t3");
	//Tmp_var.insert("t4"); Tmp_var.insert("t5"); Tmp_var.insert("t6");
	//初始化非临时变量表
	//var.insert("a"); var.insert("b"); var.insert("c");
	//var.insert("d"); var.insert("x");

	vector<Quaternion>tmp1, tmp2;
	Token token1; Token token2; Token token3;
	Quaternion quaternion1(0, 2, "wh", token1, token2, token3); //(wh,_,_,_)
	tmp1.push_back(quaternion1);

	Token token4("a","1"); Token token5("b","1"); Token token6("t1", "2");
	Quaternion quaternion2(0, 2, ">", token4, token5, token6);
	tmp1.push_back(quaternion2); //(>,a,b,t1)

	Quaternion quaternion3(0, 2, "do", token6, token1, token2);
	tmp1.push_back(quaternion3); //(do,t1,_,_)

	Token token7("t2", "2");
	Quaternion quaternion4(1, 2, "+", token4, token5, token7);
	tmp2.push_back(quaternion4); //(+,a,b,t2)

	Token token8("c", "1"); Token token9("x", "1");
	Quaternion quaternion5(1, 2, "*", token7, token8, token9);
	tmp2.push_back(quaternion5); //(*,t2,c,x)

	Quaternion quaternion6(1, 2, "we", token1, token2, token3);
	tmp2.push_back(quaternion6); //(el,_,_,_)

	qua.push_back(tmp1);
	qua.push_back(tmp2);

	//for (int i = 0; i < (int)Act_synbl.size(); i++)
	//{
	//	cout << "(" + Act_synbl[i].name + " , " + Act_synbl[i].act_inf + ")" << endl;
	//}
}

int to_int(string str)
{
	int res = 0;
	for (int j = 0; j < (int)str.size(); j++)
	{
		res = res * 10 + (str[j] - 48);
	}
	return res;
}

bool is_inActsynbl(Token token,vector<ACT_SYNBL>act_synbl)
{
	bool flag = 0;
	for (int i = 0; i < (int)act_synbl.size(); i++)
	{
		if (token.name == act_synbl[i].name) {flag = 1; break;}
	}
	return flag;
}

//填活跃信息，函数入口需要给定四元式vector，临时变量set和非临时变量set
void get_act_inf(vector< vector<Quaternion> >qua)
{
	/*int num = (int)Act_inf.size();
	for (set<string>::iterator iter = Tmp_var.begin(); iter != Tmp_var.end(); iter++)
	{
		ACT_SYNBL act_synbl(*iter, "N");
		Act_synbl.push_back(act_synbl);
	}

	for (set<string>::iterator iter = var.begin(); iter != var.end(); iter++)
	{
		ACT_SYNBL act_synbl(*iter, "Y");
		Act_synbl.push_back(act_synbl);
	}

	for (int i = (int)qua.size() - 1; i >= 0; i--)
	{
		string str1="~", str2="~", str3="~";
		for (int j = 0; j < (int)Act_synbl.size(); j++)
		{
			if (qua[i].num1.name == Act_synbl[j].name)
			{
				str1 = Act_synbl[j].act_inf; Act_synbl[j].act_inf = "Y";
			}
			if (qua[i].num2.name == Act_synbl[j].name)
			{
				str2 = Act_synbl[j].act_inf; Act_synbl[j].act_inf = "Y";
			}
			if (qua[i].ans.name == Act_synbl[j].name)
			{
				str3 = Act_synbl[j].act_inf; Act_synbl[j].act_inf = "N";
			}
		}

		Act_inf.push_back(ACT_INF(str1, str2, str3));
	}
	reverse(Act_inf.begin()+num, Act_inf.end());//倒序一下

	for (int i = 0; i < (int)Act_inf.size(); i++)
	{
		cout << "(" + Act_inf[i].num1 + " , " + Act_inf[i].num2 + " , " + Act_inf[i].ans + ")" << endl;
	}*/

	//初始化Act_synbl表，临时变量N，非临时变量Y
	for (int i = 0; i < (int)qua.size(); i++)
	{
		vector<ACT_SYNBL>act_synbl;
		for (int j = 0; j < (int)qua[i].size(); j++)
		{
			//num1不为空且不是数字时
			if (qua[i][j].num1.name != "" && qua[i][j].num1.type!="3")
			{
				if (!is_inActsynbl(qua[i][j].num1, act_synbl)) //不在表中
				{
					//当前是非临时变量
					if (qua[i][j].num1.type == "1")
					{
						ACT_SYNBL tmp(qua[i][j].num1.name, "Y");
						act_synbl.push_back(tmp);
					}
					else if (qua[i][j].num1.type == "2")//当前是临时变量
					{
						ACT_SYNBL tmp(qua[i][j].num1.name, "N");
						act_synbl.push_back(tmp);
					}
				}
			}

			//num2不为空且不是数字时
			if (qua[i][j].num2.name != "" && qua[i][j].num2.type != "3")
			{
				if (!is_inActsynbl(qua[i][j].num2, act_synbl)) //不在表中
				{
					//当前是非临时变量
					if (qua[i][j].num2.type == "1")
					{
						ACT_SYNBL tmp(qua[i][j].num2.name, "Y");
						act_synbl.push_back(tmp);
					}
					else if (qua[i][j].num2.type == "2")//当前是临时变量
					{
						ACT_SYNBL tmp(qua[i][j].num2.name, "N");
						act_synbl.push_back(tmp);
					}
				}
			}

			//ans不为空且不是数字时
			if (qua[i][j].ans.name != "" && qua[i][j].ans.type != "3")
			{
				if (!is_inActsynbl(qua[i][j].ans, act_synbl)) //不在表中
				{
					//当前是非临时变量
					if (qua[i][j].ans.type == "1")
					{
						ACT_SYNBL tmp(qua[i][j].ans.name, "Y");
						act_synbl.push_back(tmp);
					}
					else if (qua[i][j].ans.type == "2")//当前是临时变量
					{
						ACT_SYNBL tmp(qua[i][j].ans.name, "N");
						act_synbl.push_back(tmp);
					}
				}
			}
		}

		Act_synbl.push_back(act_synbl);
	}

	//for (int i = 0; i < (int)qua.size(); i++)
	//{
		//输出act_synbl
	//	for (int k = 0; k < (int)Act_synbl[i].size(); k++)
	//	{
	//		cout << i;
	//		cout << "(" + Act_synbl[i][k].name + " , " + Act_synbl[i][k].act_inf << endl;
	//	}
	//}

	//填四元式的活跃信息
	for (int i = 0; i < (int)qua.size(); i++)
	{
		vector<ACT_INF>act_inf;
		for (int j = (int)qua[i].size()-1; j >=0; j--)
		{
			ACT_INF tmp;
			for (int k = 0; k < (int)Act_synbl[i].size(); k++)
			{
				if (qua[i][j].num1.name == Act_synbl[i][k].name)
				{
					tmp.num1 = Act_synbl[i][k].act_inf;
					Act_synbl[i][k].act_inf = "Y";
				}

				if (qua[i][j].num2.name == Act_synbl[i][k].name)
				{
					tmp.num2 = Act_synbl[i][k].act_inf;
					Act_synbl[i][k].act_inf = "Y";
				}

				if (qua[i][j].ans.name == Act_synbl[i][k].name)
				{
					tmp.ans = Act_synbl[i][k].act_inf;
					Act_synbl[i][k].act_inf = "N";
				}
			}
			act_inf.push_back(tmp);
		}
		//元素反转一下
		reverse(act_inf.begin(), act_inf.end());
		Act_inf.push_back(act_inf);
	}

	//输出
	//for (int i = 0; i < (int)qua.size(); i++)
	//{
	//	for (int j = 0; j < (int)Act_inf[i].size(); j++)
	//	{
	//		cout << i;
	//		cout <<"(" + Act_inf[i][j].num1 + " , " + Act_inf[i][j].num2 + " , " + Act_inf[i][j].ans + ")" << endl;
	//	}
	//}
}

//目标代码生成
void to_objcode(vector< vector<Quaternion> >qua, vector< vector<ACT_INF> >Act_inf)
{

	for (int i = 0; i < (int)qua.size(); i++)
	{
		int wh_id = 0;
		ACT_SYNBL Rdl("", ""); //初始化R寄存器描述表
		for (int j = 0; j < (int)qua[i].size(); j++)
		{
			// 双操作数，两个操作数不可互换位置
			if (qua[i][j].op == "-" || qua[i][j].op == "/" || qua[i][j].op == "!=" ||
				qua[i][j].op == ">=" || qua[i][j].op == "<=" || qua[i][j].op == ">" ||
				qua[i][j].op == "<")
			{
				if (Rdl.name == "") //当前寄存器空闲
				{
					string tmp1 = "LD R," + qua[i][j].num1.name;
					objcode.push_back(tmp1);
				}
				else //当前寄存器不空闲
				{
					if (Rdl.name != qua[i][j].num1.name) //第一个操作数不在寄存器中
					{
						string tmp1, tmp2;
						if (Rdl.act_inf == "Y")
						{
							tmp1 = "ST R," + Rdl.name; objcode.push_back(tmp1);
							tmp2 = "LD R," + qua[i][j].num1.name;
							objcode.push_back(tmp2);
						}
						else
						{
							string tmp1 = "LD R," + qua[i][j].num1.name;
							objcode.push_back(tmp1);
						}
					}
				}

				string tmp2;
				//更新寄存器状态的活跃信息
				Rdl.act_inf = Act_inf[i][j].num1;

				if (qua[i][j].op == "-")tmp2 = "SUB R," + qua[i][j].num2.name;
				else if (qua[i][j].op == "/")tmp2 = "DIV R," + qua[i][j].num2.name;
				else if (qua[i][j].op == "!=")tmp2 = "NE R," + qua[i][j].num2.name;
				else if (qua[i][j].op == ">=")tmp2 = "GE R," + qua[i][j].num2.name;
				else if (qua[i][j].op == "<=")tmp2 = "LE R," + qua[i][j].num2.name;
				else if (qua[i][j].op == ">")tmp2 = "GT R," + qua[i][j].num2.name;
				else if (qua[i][j].op == "<")tmp2 = "LT R," + qua[i][j].num2.name;

				objcode.push_back(tmp2);
				Rdl.name = qua[i][j].ans.name; Rdl.act_inf = Act_inf[i][j].ans;//修改寄存器描述表
			}
			else if (qua[i][j].op == "+" || qua[i][j].op == "*") // +或*操作，两个操作数可以互换位置
			{
				//当前寄存器与该操作数无关
				if (Rdl.name != "" &&Rdl.name != qua[i][j].num1.name && Rdl.name != qua[i][j].num2.name)
				{
					if (Rdl.act_inf == "Y")
					{
						string tmp1 = "ST R," + Rdl.name; objcode.push_back(tmp1);
					}
				}
				else
				{
					string tmp1, tmp2;
					if (Rdl.name == qua[i][j].num1.name)
					{
						//更新寄存器状态的活跃信息
						Rdl.act_inf = Act_inf[i][j].num1;

						if (qua[i][j].op == "*") { tmp1 = "MUL R,"; }
						else if (qua[i][j].op == "+") { tmp1 = "ADD R,"; }

						objcode.push_back(tmp1 + qua[i][j].num2.name);
					}
					else if (Rdl.name == qua[i][j].num2.name)
					{
						//更新寄存器状态的活跃信息
						Rdl.act_inf = Act_inf[i][j].num1;

						if (qua[i][j].op == "*") { tmp1 = "MUL R,"; }
						else if (qua[i][j].op == "+") { tmp1 = "ADD R,"; }

						objcode.push_back(tmp1 + qua[i][j].num1.name);
					}
					else
					{
						tmp1 = "LD R," + qua[i][j].num1.name;
						objcode.push_back(tmp1);
						if (qua[i][j].op == "*") { tmp2 = "MUL R,"; }
						else if (qua[i][j].op == "+") { tmp2 = "ADD R,"; }

						objcode.push_back(tmp2 + qua[i][j].num2.name);
					}
				}

				Rdl.name = qua[i][j].ans.name; Rdl.act_inf = Act_inf[i][j].ans;//修改寄存器描述表
			}
			else if (qua[i][j].op == "if" || qua[i][j].op == "el" || qua[i][j].op == "ie")
			{
				//更新寄存器状态的活跃信息
				if(qua[i][j].op=="if")Rdl.act_inf = Act_inf[i][j].num1;
				if (Rdl.act_inf == "Y") { objcode.push_back("ST R," + Rdl.name); Rdl.act_inf = "N"; }

				string tmp;
				if (qua[i][j].op == "if") { tmp = "FJ R,"; objcode.push_back(tmp); }
				else if (qua[i][j].op == "el") { tmp = "JMP "; objcode.push_back(tmp); }
				//当前SEM栈不为空时，先退栈返填
				if (!SEM.empty())
				{
					string tmp = SEM.top();
					SEM.pop();

					objcode[to_int(tmp)] = objcode[to_int(tmp)] + to_string(objcode.size());
				}
				if(qua[i][j].op != "ie")SEM.push(to_string(objcode.size()-1));

			}
			else if (qua[i][j].op == "wh" || qua[i][j].op == "do" || qua[i][j].op == "we")
			{
				//更新寄存器状态的活跃信息
				if (qua[i][j].op == "do")Rdl.act_inf = Act_inf[i][j].num1;
				if (Rdl.act_inf == "Y") { objcode.push_back("ST R," + Rdl.name); Rdl.act_inf = "N"; }

				string tmp;
				if (qua[i][j].op == "wh") { wh_id = (int)objcode.size(); }
				else if (qua[i][j].op == "do") { tmp = "FJ R,"; objcode.push_back(tmp); }
				else if (qua[i][j].op == "we") { tmp = "JMP "+to_string(wh_id); objcode.push_back(tmp); }
				//当前SEM栈不为空时，先退栈返填
				if (!SEM.empty())
				{
					string tmp = SEM.top();
					SEM.pop();

					objcode[to_int(tmp)] = objcode[to_int(tmp)] + to_string(objcode.size());
				}
				if (qua[i][j].op == "do")SEM.push(to_string(objcode.size() - 1));

			}
			else if (qua[i][j].op == "lb" || qua[i][j].op == "gt")
			{
				string tmp;
				if (qua[i][j].op == "lb") { tmp = qua[i][j].ans.name + ":"; }
				else if (qua[i][j].op == "gt") { tmp = "JMP " + qua[i][j].ans.name; }

				objcode.push_back(tmp);
			}
			else if (qua[i][j].op == "=")
			{
				string tmp1,tmp2;
				if (Rdl.name != qua[i][j].num1.name)//寄存器中不是当前操作数
				{
					if (Rdl.act_inf == "Y") { tmp1 = "ST R," + Rdl.name; objcode.push_back(tmp1); }
					tmp2 = "LD R," + qua[i][j].num1.name;
					objcode.push_back(tmp2);
				}

				Rdl.act_inf = Act_inf[i][j].num1; //更新寄存器活跃信息

				Rdl.name = qua[i][j].ans.name; Rdl.act_inf = Act_inf[i][j].ans;
			}
			else //其他情况
			{

			}
		}
		if (Rdl.act_inf == "Y") { objcode.push_back("ST R," + Rdl.name); }
	}

	//输出目标代码
	for (int i = 0; i < (int)objcode.size(); i++)
	{
		cout <<std::left<<setw(10)<< i << std::left << setw(10) << objcode[i] << endl;
	}
}

void run()
{
	//init();
	get_act_inf(qua);
	to_objcode(qua, Act_inf);
}

};

#endif // _target_H
