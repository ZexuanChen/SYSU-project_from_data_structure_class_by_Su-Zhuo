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

map<char, int> m {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}}; //������������ȼ����� 

class Calculator {
public:
	Calculator(); //Ĭ�Ϲ��캯�� 
	~Calculator(); //�������� 
	void clear(); //��ճ�Ա����
	void getS(string s); //��ñ��ʽ 
	int getRes(); //���ؽ��
	void eval(); //������ʽ
	void process(char ch); //�����������ĵ������� 
	string stackToStr(int flag); //��ջ������ת�����ַ����Ա�չʾ 
	void show(int witch, string opt, int pos); //��ʾ���� 
private:
	stack<char> opt_stack; //�����ջ 
	stack<int> num_stack; //������ջ 
	string expression; //���ʽ 
	int res, cnt; //������������ 
};

#endif
