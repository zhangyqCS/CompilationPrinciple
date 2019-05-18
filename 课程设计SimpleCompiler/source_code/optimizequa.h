#ifndef _optimizequa_H
#define _optimizequa_H
#include <iostream>
#include <cstring>
#include <stdio.h>
#include<stdlib.h>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e2 + 5;

struct Opt {

struct token {
    string name;
    string type;     //2为临时变量，3为数字，1为非临时变量
};

struct Quaternion {      //四元式结构体
    int block;           //基本块标识
    int type;            //类型-0 1 2 3
    string op;           //操作
    token num1;         //操作数1
    token num2;         //操作数2
    token ans;          //结果
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

vector< vector<ACT_INF> >Act_inf;
vector< vector<ACT_SYNBL> >Act_synbl;
vector<string>objcode;
stack<string>SEM; //保存待返填地址

struct Quaternion qua[maxn];   //四元式数组
vector<Quaternion> Block[15];
vector<vector<Quaternion>> ToTarget;
struct Node {                //DAG节点
    int left;
    int right;
    int id;
    string op;
    token m_sign;                    //主标记
    token sign[maxn];                  //附加标记
};

struct DAG{                  //DAG
    int num=0;
    Node node[maxn];
}dag;

void init();     //初始化四元式结构体数组
void addition(int n,string A,string typ);   //把标记A添加到节点n上，顺便删除无用标记
int getnode(string B);   //获取标记为B的节点的id
void makeleaf(string B,string typ);   //构造叶子节点
void delnode(int n);     //删除id为n的节点
int findnode(string opl,string B,string C);   //在DAG中查找有无符合A=B op C的节点
int makenode(string opl,string B,string C);  //构造中间节点
string coutvalue(string opl,string B,string C);   //计算两个数运算的值
void makequa(int block);   //生成block块中优化后的四元式
void deletedag();  //对dag清零
void optimizequa(int block_num);    //优化四元式
int divide();             //划分基本块
void run();

int to_int(string str)
{
	int res = 0;
	for (int j = 0; j < (int)str.size(); j++)
	{
		res = res * 10 + (str[j] - 48);
	}
	return res;
}

bool is_inActsynbl(token token1,vector<ACT_SYNBL>act_synbl)
{
	bool flag = 0;
	for (int i = 0; i < (int)act_synbl.size(); i++)
	{
		if (token1.name == act_synbl[i].name) {flag = 1; break;}
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

void get_objcode()
{
	get_act_inf(ToTarget);
	to_objcode(ToTarget, Act_inf);
}

};

#endif // _optimizequa_H
