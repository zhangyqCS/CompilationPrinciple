#ifndef _lexical_H
#define _lexical_H
#include<cstdio>
#include<vector>
#include<cstdlib>
#include<algorithm>
#include<string>
#include<stack>
#include<iostream>
#include<utility>
#include<map>
#include<iomanip>
struct ZYQ {

struct TOKEN
{
	int i;
	int j;
	int Vt_id;
	TOKEN(int a = 0, int b = 0, int c = 0)
	{
		i = a, j = b, Vt_id = c;
	}
};

vector<string>TOKEN_k; //¹Ø¼ü×Ö±í
vector<string>TOKEN_p; //½ç·û±í
vector<string>TOKEN_i; //±êÊ¶·û±í
vector<string>TOKEN_c; //Êý×Ö³£Á¿±í
vector<string>TOKEN_strc; //×Ö·û´®³£Á¿±í
vector<string>TOKEN_charc; //×Ö·û³£Á¿±í
map<string, int>Vt; //ËùÓÐÖÕ½á·ûÀàÐÍµÄÓ³Éä
vector<TOKEN>Token;

int state, level, fnum, array_len,Vt_num;
int error_flag = 0; //±àÒë´íÎó±êÖ¾
int file_flag = 0; //ÎÄ¼þ¶ÁÈ¡µÄ±êÖ¾

unsigned int i = 0;
string str;
string input_str;

bool is_Char(char c) //ÅÐ¶ÏÊÇ·ñÊÇ×Ö·û
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))return true;
	else
		return false;
}

bool is_Dig(char c) //ÅÐ¶ÏÊÇ·ñÊÇÊý×Ö
{
	if (c >= '0' && c <= '9')return true;
	else
		return false;
}

void next_state(char ch) //自动机状态转移函数
{
	if (state == 0)
	{

		if (is_Char(ch)) { state = 1; str.push_back(ch); } // δ(0,字母)=1
		else if (is_Dig(ch)) { state = 3; str.push_back(ch); } // δ(0,数字)=3
		else if (ch == '=') { state = 8; str.push_back(ch); } // δ(0,'=')=8
		else if (ch == '>') { state = 11; str.push_back(ch); } // δ(0,'>')=11
		else if (ch == '<') { state = 14; str.push_back(ch); } // δ(0,'<')=14
		else if (ch == '+') { state = 17; str.push_back(ch); } // δ(0,'+')=17
		else if (ch == '-') { state = 21; str.push_back(ch); } // δ(0,'-')=21
		else if (ch == '*') { state = 25; str.push_back(ch); } // δ(0,'*')=25
		else if (ch == '/') { state = 28; str.push_back(ch); } // δ(0,'/')=28
		else if (ch == '{') { state = 31; str.push_back(ch); } // δ(0,'{')=31
		else if (ch == '}') { state = 32; str.push_back(ch); } // δ(0,'}')=32
		else if (ch == '(') { state = 33; str.push_back(ch); } // δ(0,'(')=33
		else if (ch == ')') { state = 34; str.push_back(ch); } // δ(0,')')=34
		else if (ch == '[') { state = 35; str.push_back(ch); } // δ(0,'[')=35
		else if (ch == ']') { state = 36; str.push_back(ch); } // δ(0,']')=36
		else if (ch == ',') { state = 37; str.push_back(ch); } // δ(0,',')=37
		else if (ch == ';') { state = 38; str.push_back(ch); } // δ(0,';')=38
		else if (ch == 39) { state = 39; str.push_back(ch); } // δ(0,''')=39
		else if (ch == 34) { state = 41; str.push_back(ch); } // δ(0,'"')=41

	}
	else if (state == 1)
	{
		if (is_Char(ch) || is_Dig(ch) || ch == '_') { state = 1; str.push_back(ch); } // δ(1,字符或数字)=1
		else if (ch == '[')
		{
			state = 43; str.push_back(ch);// δ(1,[)=43
		}
		else
		{
			state = 2; i = i - 1; // δ(1,其他)=2
		}
	}
	else if (state == 3)
	{
		if (is_Dig(ch)) { state = 3; str.push_back(ch); } // δ(3,数字=3
		else if (ch == '.') { state = 4; str.push_back(ch); } // δ(3,'.')=4
		else
		{
			state = 7; i = i - 1; // δ(3,其他)=7
		}
	}
	else if (state == 4)
	{
		if (is_Dig(ch)) { state = 5; str.push_back(ch); } // δ(4,数字)=5
		else
		{
			error_flag = 1; //其他情况，编译出错
		}
	}
	else if (state == 5)
	{
		if (is_Dig(ch)) { state = 5; str.push_back(ch); } // δ(5,数字)=5
		else
		{
			state = 6; i = i - 1; // δ(5,其他)=6
		}
	}
	else if (state == 8)
	{
		if (ch == '=') { state = 9; str.push_back(ch); } // δ(8,'=')=9
		else
		{
			state = 10; i = i - 1; // δ(8,其他)=10
		}
	}
	else if (state == 11)
	{
		if (ch == '=') { state = 12; str.push_back(ch); } // δ(11,'=')=12
		else
		{
			state = 13; i = i - 1; // δ(11,其他)=13
		}
	}
	else if (state == 14)
	{
		if (ch == '=') { state = 15; str.push_back(ch); } // δ(14,'=')=15
		else
		{
			state = 16; i = i - 1; // δ(14,其他)=16
		}
	}
	else if (state == 17)
	{
		if (ch == '+') { state = 18; str.push_back(ch); } // δ(17,'+')=18
		else if (ch == '=') { state = 19; str.push_back(ch); } // δ(17,'=')=19
		else
		{
			state = 20; i = i - 1; // δ(17,其他)=20
		}
	}
	else if (state == 21)
	{
		if (ch == '-') { state = 22; str.push_back(ch); } // δ(21,'-')=22
		else if (ch == '=') { state = 23; str.push_back(ch); } // δ(21,'=')=23
		else
		{
			state = 24; i = i - 1; // δ(21,其他)=24
		}
	}
	else if (state == 25)
	{
		if (ch == '=') { state = 26; str.push_back(ch); } // δ(25,'=')=26
		else
		{
			state = 27; i = i - 1; // δ(25,其他)=27
		}
	}
	else if (state == 28)
	{
		if (ch == '=') { state = 29; str.push_back(ch); } // δ(28,'=')=29
		else
		{
			state = 30; i = i - 1; // δ(28,其他)=30
		}
	}
	else if (state == 39)
	{
		if (ch == 39) { state = 40; str.push_back(ch); } // δ(39,''')=40
		else
		{
			state = 39; str.push_back(ch); // δ(39,其他)=39
		}
	}
	else if (state == 41)
	{
		if (ch == 34) { state = 42; str.push_back(ch); } // δ(41,'"')=42
		else
		{
			state = 41; str.push_back(ch); // δ(41,其他)=41
		}
	}
	else if (state == 43)
	{
		if (is_Dig(ch)) { state = 43; str.push_back(ch);}
		else if (ch == ']') { state = 2; str.push_back(ch); }
		else
		{
			error_flag = 1;//编译出错
		}
	}
}

bool is_KI() //¹Ø¼ü×Ö»ò±êÊ¶·û
{
	if (state == 2)return true;
	else
		return false;
}

bool is_C() //Êý×Ö³£Á¿
{
	if (state == 6 || state == 7)return true;
	else
		return false;
}

bool is_CHARC() //×Ö·û³£Á¿
{
	if (state == 40)return true;
	else
		return false;
}

bool is_STR_C() //×Ö·û´®³£Á¿
{
	if (state == 42)return true;
	else
		return false;
}

bool is_P() //½ç·û
{
	if (state == 9 || state == 10 || state == 12 || state == 13 || state == 15 || state == 16 ||
		(state >= 18 && state <= 20) || (state >= 22 && state <= 24) || state == 26 || state == 27 ||
		(state >= 29 && state <= 38))return true;
	else
		return false;
}

/*int to_int(string str)
{
	int res = 0;
	for (int j = 0; j < (int)str.size(); j++)
	{
		res = res * 10 + (str[j] - 48);
	}
	return res;
}*/

/*void TABEL::Tabel_init()
{
	//³õÊ¼»¯»ù±¾ÀàÐÍÕ¼µÄ×Ö½ÚÊý
	mp["char"] = 1; mp["int"] = 4; mp["float"] = 4; mp["double"] = 8;
}*/

/*void TABEL::Print_tabel()
{
	cout << "SYNBL:" << endl;
	cout << std::left << setw(15)<<"IDX"<<std::left << setw(15) << "NAME" << std::left << setw(15) << "TYP";
	cout << std::left << setw(15) << "CAT" << std::left << setw(15) << "ADDR" << endl;
	for (unsigned int j = 0; j < Synbl.size(); j++)
	{
		cout << std::left << setw(15) << j << std::left << setw(15) << Synbl[j].name;
		cout << std::left << setw(15) << "(" + Synbl[j].typ.first + ',' + to_string(Synbl[j].typ.second) + ")";
		cout << std::left<<setw(15) << Synbl[j].cat << std::left<<setw(15) << "("+Synbl[j].addr.first +',' +to_string(Synbl[j].addr.second) + ")" << endl;
	}
	cout<< " "<<endl;

	cout << "TAPEL:" << endl;
	cout << std::left << setw(15) << "IDX" << std::left << setw(15) << "TVAL";
	cout << std::left << setw(15) << "TPOINT"<<endl;
	for (unsigned int j = 0; j < Tapel.size(); j++)
	{
		//cout << Tapel[j].tval << ",(" << Tapel[j].tpoint.first << ',' << Tapel[j].tpoint.second << ")" << endl;
		cout << std::left << setw(15) << j << std::left << setw(15) << Tapel[j].tval;
		cout << std::left << setw(15) << "(" + Tapel[j].tpoint.first + ',' + to_string(Tapel[j].tpoint.second) + ")" << endl;
	}
	cout << " " << endl;

	cout << "AINFL:" << endl;
	cout << std::left << setw(15) << "IDX" << std::left << setw(15) << "LOW" << std::left << setw(15) << "UP";
	cout << std::left << setw(15) << "CTP" << std::left << setw(15) << "CLEN" << endl;
	for (unsigned int j = 0; j < Ainfl.size(); j++)
	{
		cout << std::left << setw(15) << j << std::left << setw(15) << Ainfl[j].low << std::left << setw(15) << Ainfl[j].up;
		cout << std::left << setw(15) << Ainfl[j].ctp << std::left << setw(15) << Ainfl[j].clen << endl;
		//cout << Ainfl[j].low << ',' << Ainfl[j].up << ',' << Ainfl[j].ctp << ',' << Ainfl[j].clen << endl;
	}
	cout << " " << endl;

	cout << "PFINFL:" << endl;
	cout << std::left << setw(15) << "IDX" << std::left << setw(15) << "LEVEL" << std::left << setw(15) << "OFF";
	cout << std::left << setw(15) << "FN" << std::left << setw(15) << "ENTRY" << std::left << setw(15) << "PARAM" << endl;
	for (unsigned int j = 0; j < Pfinfl.size(); j++)
	{
		cout << std::left << setw(15) << j << std::left << setw(15) << Pfinfl[j].level;
		cout << std::left << setw(15) << "(" + Pfinfl[j].off.first + ',' + to_string(Pfinfl[j].off.second) + ")";
		cout << std::left << setw(15) << Pfinfl[j].fn << std::left << setw(15) << Pfinfl[j].entry;
		cout << std::left << setw(15) << "(" + Pfinfl[j].param.first + ',' + to_string(Pfinfl[j].param.second) + ")" << endl;
		//cout << Pfinfl[j].level << ",(" << Pfinfl[j].off.first << ',' << Pfinfl[j].off.second << ")," <<
		//	Pfinfl[j].fn << ',' << Pfinfl[j].entry << ",("<< Pfinfl[j].param.first << ',' <<
		//	Pfinfl[j].param.second << ')' << endl;
	}
	cout << " " << endl;

	cout << "CONSL:" << endl;
	cout << std::left << setw(15) << "IDX" << std::left << setw(15) << "VALUE" << endl;
	for (unsigned int j = 0; j < Consl.size(); j++)
	{
		cout << std::left << setw(15)<<j<< std::left << setw(15)<<Consl[j] << endl;
	}
	cout << " " << endl;

	cout << "LENL:" << endl;
	cout << std::left << setw(15) << "IDX" << std::left << setw(15) << "VALUE" << endl;
	for (unsigned int j = 0; j < Lenl.size(); j++)
	{
		cout << std::left << setw(15)<<j<< std::left << setw(15)<< Lenl[j] << endl;
	}
	cout << " " << endl;
}*/

/*void lexical_analysis1() //ÓÐ·ûºÅ±í
{
	TABEL tabel;
	tabel.Tabel_init();

	state = 0; error_flag = 0; file_flag = 0;
	level = 0; Vt_num = 4;
	Vt["Iden"] = 0;Vt["Num"] = 1;Vt["Strc"] = 2;Vt["Charc"] = 3;
	while (getline(cin, input_str))
	{

		if (input_str == "#") { file_flag++; continue; }

		if (file_flag == 0) { TOKEN_k.push_back(input_str); Vt[input_str] = Vt_num; Vt_num++; }
		else if (file_flag == 1) { TOKEN_p.push_back(input_str); Vt[input_str] = Vt_num; Vt_num++; }
		else
		{
			i = 0; decl_flag = 0; array_flag = 0; func_flag = 0;
			fnum = 0; array_len = 0;
			string decl_type, func_name;

			while (i < input_str.size())
			{
				error_flag = 0;
				next_state(input_str[i]); //µ÷ÓÃ×´Ì¬×ªÒÆº¯Êý
				if (error_flag != 0) { break; } //±àÒë³ö´í

				if (is_KI()) //¹Ø¼ü×Ö»ò±êÊ¶·û
				{
					bool flag_k = 0, flag_i = 0;

					for (unsigned int j = 0; j < TOKEN_k.size(); j++) //ÔÚkey±íÖÐ²éÑ¯
					{
						if (str == TOKEN_k[j])
						{
							//¹Ø¼ü×ÖÎªchar,double,float,intÊ±ÎªÉùÃ÷Óï¾ä
							if (j == 0 || j == 2 || j == 4 || j == 7) { decl_flag = 1; decl_type = TOKEN_k[j]; }
							//ans.push_back(make_pair('k', j)); flag_k = 1;
							TOKEN token(0, j, Vt[TOKEN_k[j]]); flag_k = 1;
							Token.push_back(token);
						}
					}

					if (flag_k == 0) //key±íÖÐÎÞ´Ë´®
					{
						if (decl_flag == 1) //ÉùÃ÷Óï¾ä
						{
							for (int j = 0; j < (int)TOKEN_i.size(); j++) //ÔÚ±êÊ¶·û±íÖÐ²éÑ¯
							{
								if (str == TOKEN_i[j]) { error_flag = 1; break; }
							}
							if (error_flag == 1)break; //ÖØ¸´¶¨Òå

							if (func_flag == 1) //º¯ÊýÉùÃ÷
							{
								tabel.VALL.push(str);
								pair<string, int> p1 = make_pair(decl_type, -1);
								pair<string, int> p2 = make_pair("VALL", tabel.VALL.size());
								SYNBL synbl(str, p1, "vf", p2);
								tabel.Synbl.push_back(synbl);
								fnum++;
								if (input_str[i + 1] == ')')
								{
									pair<string, int> p3 = make_pair("SYNBL", (int)tabel.Synbl.size() - fnum);
									pair<string, int> p13 = make_pair("VALL", tabel.VALL.size() - fnum);
									PFINFL pfinfl(level, p13, fnum, -1, p3);
									tabel.Pfinfl.push_back(pfinfl);
								}
							}
							else if (input_str[i + 1] == '[') //Êý×é
							{
								array_flag = 1;

								AINFL ainfl(0, 0, decl_type, tabel.mp[decl_type]);
								tabel.Ainfl.push_back(ainfl);
								pair<string, int> p4 = make_pair("AINFL", (int)tabel.Ainfl.size() - 1);
								TAPEL tapel("array", p4);
								tabel.Tapel.push_back(tapel);

								pair<string, int> p5 = make_pair("TAPEL", (int)tabel.Tapel.size() - 1);
								pair<string, int> p6 = make_pair("LENL", (int)tabel.Lenl.size());
								SYNBL synbl(str, p5, "array", p6);
								tabel.Synbl.push_back(synbl);
							}
							else if (input_str[i + 1] == '(') //º¯ÊýÃû×Ö
							{
								func_flag = 1; func_name = str;
								pair<string, int> p7 = make_pair(decl_type, -1);
								pair<string, int> p8 = make_pair("PFINFL", (int)tabel.Pfinfl.size());
								SYNBL synbl(func_name, p7, "func", p8);
								tabel.Synbl.push_back(synbl);
								tabel.VALL.push(func_name);
							}
							else //ÆÕÍ¨±êÊ¶·û
							{
								if (input_str[i + 1] == '=') //ÉùÃ÷Ê±¸³Óè³õÖµ
								{
									pair<string, int> p9 = make_pair(decl_type, -1);
									pair<string, int> p10 = make_pair("CONSL", (int)tabel.Consl.size());
									SYNBL synbl(str, p9, "const", p10);
									tabel.Synbl.push_back(synbl);
								}
								else
								{
									pair<string, int> p11 = make_pair(decl_type, -1);
									pair<string, int> p12 = make_pair("CONSL", -1);
									SYNBL synbl(str, p11, "const", p12);
									tabel.Synbl.push_back(synbl);
								}
							}
							TOKEN_i.push_back(str); //ans.push_back(make_pair('i', TOKEN_i.size() - 1));
							TOKEN token(1, TOKEN_i.size()-1, Vt["Iden"]);
							Token.push_back(token);
						}
						else //·ÇÉùÃ÷Óï¾ä
						{
							for (int j = 0; j < (int)TOKEN_i.size(); j++) //ÔÚ±êÊ¶·û±íÖÐ²éÑ¯
							{
								if (str == TOKEN_i[j]) { flag_i = 1; break; }
							}
							if (flag_i == 0) { error_flag = 2; break; } //±êÊ¶·ûÃ»¶¨Òå
						}

					}
					state = 0;
					str.clear();
				}
				else if (is_P()) //½ç·û
				{
					bool flag_p = 0;
					for (unsigned int j = 0; j < TOKEN_p.size(); j++) //ÔÚ½ç·û±íÖÐ²éÑ¯
					{
						if (str == TOKEN_p[j])
						{
							//ans.push_back(make_pair('p', j)); flag_p = 1;
							TOKEN token(2, j, Vt[TOKEN_p[j]]); flag_p = 1;
							Token.push_back(token);
						}
					}
					if (flag_p == 0) { error_flag = 3; break; }//±íÖÐ²î²»µ½£¬±àÒë³ö´í

					state = 0;
					str.clear();
				}
				else if (is_C()) //ÊýÖµ³£Á¿
				{

					if (decl_flag == 1)
					{
						if (array_flag == 1)
						{
							int num = to_int(str);
							tabel.Ainfl[(int)tabel.Ainfl.size() - 1].up = num;
							array_len = tabel.Ainfl[(int)tabel.Ainfl.size() - 1].up*tabel.Ainfl[(int)tabel.Ainfl.size() - 1].clen;
							tabel.Lenl.push_back(to_string(array_len));
						}
						else
						{
							tabel.Consl.push_back(str);
						}
					}
					bool flag_c = 0;
					for (unsigned int j = 0; j < TOKEN_c.size(); j++) //ÔÚ³£Á¿±íÖÐ²éÑ¯
					{
						if (str == TOKEN_c[j])
						{
							//ans.push_back(make_pair('c', j)); flag_c = 1;
							TOKEN token(3, j, Vt["Num"]); flag_c = 1;
							Token.push_back(token);
						}
					}
					if (flag_c == 0)
					{
						TOKEN_c.push_back(str); //ans.push_back(make_pair('c', TOKEN_c.size() - 1));
						TOKEN token(3, TOKEN_c.size()-1, Vt["Num"]);
						Token.push_back(token);
					}
					//±íÖÐ²é²»µ½£¬½«Æä¼Óµ½±íÎ²
					state = 0;
					str.clear();
				}
				else if (is_STR_C()) //×Ö·û´®³£Á¿
				{
					bool flag_strc = 0;

					for (unsigned int j = 0; j < TOKEN_strc.size(); j++) //ÔÚ³£Á¿±íÖÐ²éÑ¯
					{
						if (str == TOKEN_strc[j])
						{
							//ans.push_back(make_pair('s', j)); flag_strc = 1;
							TOKEN token(4, j, Vt["Strc"]); flag_strc = 1;
							Token.push_back(token);
						}
					}
					if (flag_strc == 0) //±íÖÐ²é²»µ½£¬½«Æä¼Óµ½±íÎ²
					{
						TOKEN_strc.push_back(str); //ans.push_back(make_pair('s', TOKEN_strc.size() - 1));
						TOKEN token(4, TOKEN_strc.size()-1, Vt["Strc"]); //flag_strc = 1;
						Token.push_back(token);
					}
					state = 0;
					str.clear();
				}
				else if (is_CHARC()) //×Ö·û³£Á¿
				{
					bool flag_charc = 0;
					for (unsigned int j = 0; j < TOKEN_charc.size(); j++) //ÔÚ³£Á¿±íÖÐ²éÑ¯
					{
						if (str == TOKEN_charc[j])
						{
							//ans.push_back(make_pair('C', j)); flag_charc = 1;
							TOKEN token(5, j, Vt["Charc"]); flag_charc = 1;
							Token.push_back(token);
						}
					}
					if (flag_charc == 0)
					{
						TOKEN_charc.push_back(str); //ans.push_back(make_pair('C', TOKEN_charc.size() - 1));
						TOKEN token(5, TOKEN_charc.size()-1, Vt["Charc"]); //flag_charc = 1;
						Token.push_back(token);
					}
					//±íÖÐ²é²»µ½£¬½«Æä¼Óµ½±íÎ²
					state = 0;
					str.clear();
				}

				i++;
			}
			if (error_flag == 1) { printf("±êÊ¶·ûÖØ¸´¶¨Òå!!\n"); break; }
			else if (error_flag == 2) { printf("±êÊ¶·ûÃ»ÓÐ¶¨Òå!!\n"); break; }
			else if (error_flag == 3) { printf("¸Ã³ÌÐò±àÒë³ö´í!!\n"); break; }
		}
	}

	tabel.Print_tabel();
	for (unsigned int j = 0; j < Token.size(); j++)
	{
		printf("(%d , %d , %d)\n", Token[j].i, Token[j].j, Token[j].Vt_id);
	}
}*/

vector<string> strs;

void lexical_analysis(vector<string> &lines, string &S) //Ö»Éú³ÉToken´®£¬ÎÞ·ûºÅ±í
{
	state = 0; error_flag = 0; file_flag = 0;
	Vt_num = 4;
	Vt["Iden"] = 0; Vt["Num"] = 1; Vt["Strc"] = 2; Vt["Charc"] = 3;
	int line = 1;
	while (getline(cin, input_str))
	{
	    if(input_str.size() == 0) continue;
	    printf("line %d: ", line++);

		//if (input_str == "#") { file_flag++; continue; }

		//if (file_flag == 0) { TOKEN_k.push_back(input_str); Vt[input_str] = Vt_num; Vt_num++; }
		//else if (file_flag == 1) { TOKEN_p.push_back(input_str); Vt[input_str] = Vt_num; Vt_num++; }
		//else
		if(input_str != "#")
		{
			i = 0;
			strs.clear();
			while (i < input_str.size())
			{
				error_flag = 0;
				next_state(input_str[i]); //µ÷ÓÃ×´Ì¬×ªÒÆº¯Êý
				if (error_flag == 1) { break; } //±àÒë³ö´í
				if (is_KI()) //¹Ø¼ü×Ö»ò±êÊ¶·û
				{
				    strs.push_back(str);
                    cout << str << " ";
					bool flag_k = 0, flag_i = 0;

					for (unsigned int j = 0; j<TOKEN_k.size(); j++) //ÔÚkey±íÖÐ²éÑ¯
					{
						if (str == TOKEN_k[j])
						{
							TOKEN token(0, j, Vt[TOKEN_k[j]]); flag_k = 1;
							Token.push_back(token);
						}
					}

					if (flag_k == 0) //key±íÖÐÎÞ´Ë´®
					{
						for (unsigned int j = 0; j<TOKEN_i.size(); j++) //ÔÚ±êÊ¶·û±íÖÐ²éÑ¯
						{
							if (str == TOKEN_i[j])
							{
								TOKEN token(1, j, Vt["Iden"]); flag_i = 1;
								Token.push_back(token);
							}
						}
						if (flag_i == 0)  //±íÖÐ²é²»µ½£¬½«Æä¼Óµ½±íÎ²
						{
							TOKEN_i.push_back(str);
							TOKEN token(1, TOKEN_i.size() - 1, Vt["Iden"]);
							Token.push_back(token);
						}
					}

					state = 0;
					str.clear();
				}
				else if (is_P()) //½ç·û
				{
                    strs.push_back(str);
                    cout << str << " ";
					for (unsigned int j = 0; j<TOKEN_p.size(); j++) //ÔÚ½ç·û±íÖÐ²éÑ¯
					{
						if (str == TOKEN_p[j])
						{
							TOKEN token(2, j, Vt[TOKEN_p[j]]);
							Token.push_back(token);
						}
					}
					state = 0;
					str.clear();
				}
				else if (is_C()) //ÊýÖµ³£Á¿
				{
				    strs.push_back(str);
                    cout << str << " ";
					bool flag_c = 0;

					for (unsigned int j = 0; j<TOKEN_c.size(); j++) //ÔÚ³£Á¿±íÖÐ²éÑ¯
					{
						if (str == TOKEN_c[j])
						{
							//ans.push_back(make_pair('c', j)); flag_c = 1;
							TOKEN token(3, j, Vt["Num"]); flag_c = 1;
							Token.push_back(token);
						}
					}
					if (flag_c == 0) //±íÖÐ²é²»µ½£¬½«Æä¼Óµ½±íÎ²
					{
						TOKEN_c.push_back(str);
						TOKEN token(3, TOKEN_c.size() - 1, Vt["Num"]);
						Token.push_back(token);
					}
					state = 0;
					str.clear();
				}
				else if (is_STR_C()) //×Ö·û´®³£Á¿
				{
				    strs.push_back(str);
                    cout << str << " ";
					bool flag_strc = 0;

					for (unsigned int j = 0; j<TOKEN_strc.size(); j++) //ÔÚ³£Á¿±íÖÐ²éÑ¯
					{
						if (str == TOKEN_strc[j])
						{
							TOKEN token(4, j, Vt["Strc"]); flag_strc = 1;
							Token.push_back(token);
						}
					}
					if (flag_strc == 0) //±íÖÐ²é²»µ½£¬½«Æä¼Óµ½±íÎ²
					{
						TOKEN_strc.push_back(str);
						TOKEN token(4, TOKEN_strc.size() - 1, Vt["Strc"]);
						Token.push_back(token);
					}

					state = 0;
					str.clear();
				}
				else if (is_CHARC()) //×Ö·û³£Á¿
				{
				    strs.push_back(str);
                    cout << str << " ";
					bool flag_charc = 0;

					for (unsigned int j = 0; j<TOKEN_charc.size(); j++) //ÔÚ³£Á¿±íÖÐ²éÑ¯
					{
						if (str == TOKEN_charc[j])
						{
							TOKEN token(5, j, Vt["Charc"]); flag_charc = 1;
							Token.push_back(token);
						}
					}
					if (flag_charc == 0) //±íÖÐ²é²»µ½£¬½«Æä¼Óµ½±íÎ²
					{
						TOKEN_charc.push_back(str);
						TOKEN token(5, TOKEN_charc.size() - 1, Vt["Charc"]);
						Token.push_back(token);
					}

					state = 0;
					str.clear();
				}

				i++;
			}
			cout << endl;
			if (error_flag == 1) { printf("±àÒë³ÌÐò³ö´í!!\n"); break; }
		}
		else {
            strs.clear();
            strs.push_back("#");
            cout << "#" << endl;
		}
		string temp;
        for(auto x : strs) {
            temp += x + " ";
            S += x + " ";
        }
        //cout << temp << endl;
        if(temp.size() == 0) continue;
        lines.push_back(temp);
	}

	//Êä³ö½á¹û
	for (unsigned int j = 0; j < Token.size(); j++)
	{
//		//printf("(%d , %d , %d)\n", Token[j].i, Token[j].j, Token[j].Vt_id);
//		if (Token[j].i == 0)cout << TOKEN_k[Token[j].j] << endl;
//		else if(Token[j].i == 1)cout << TOKEN_i[Token[j].j] << endl;
//		else if(Token[j].i == 2)cout << TOKEN_p[Token[j].j] << endl;
//		else if(Token[j].i == 3)cout << TOKEN_c[Token[j].j] << endl;
//		else if(Token[j].i == 4)cout << TOKEN_strc[Token[j].j] << endl;
//		else if(Token[j].i == 5)cout << TOKEN_charc[Token[j].j] << endl;
	}
}

void run()
{
	//In(); Out(); //´Óc_in.txtÎÄ¼þÖÐ¶ÁÈëÊý¾Ý£¬²¢½«Êý¾Ý½á¹ûÐ´Èëc_out.txtÖÐ
	//lexical_analysis();

//	return 0;
}


};

#endif // _lexical_H
