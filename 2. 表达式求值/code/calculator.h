#ifndef Calculator_H
#define Calculator_H
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <stack>
#include <map>
using namespace std;

map<char, int> m {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}}; //部分运算符优先级定义 

class Calculator {
public:
	Calculator(); //默认构造函数 
	~Calculator(); //析构函数 
	void clear(); //清空成员变量
	void getS(string s); //获得表达式 
	int getRes(); //返回结果
	void eval(); //计算表达式
	void process(char ch); //运算符弹出后的单步运算 
	string stackToStr(int flag); //将栈的内容转换成字符串以便展示 
	void show(int witch, string opt, int pos); //显示过程 
private:
	stack<char> opt_stack; //运算符栈 
	stack<int> num_stack; //运算数栈 
	string expression; //表达式 
	int res, cnt; //结果、步骤计数 
};

#endif
