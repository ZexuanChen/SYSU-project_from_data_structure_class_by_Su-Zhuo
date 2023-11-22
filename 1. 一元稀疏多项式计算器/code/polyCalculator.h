#ifndef polyCalculator_H
#define polyCalculator_H
#define PII pair<double, double>//firstΪָ����secondΪϵ�� 
#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;

//���׶���ʽ��������
class polyCalculator {
	vector<PII> poly[2], res; //vector��Ԫ��Ϊ (ָ����ϵ��)�ԣ�ͳһ������vector�����洢�������ʽ����һ��vector�����洢�������ʽ
	
public:
	polyCalculator(); //���캯�� 
	~polyCalculator(); //��������
	void clear(); //��ճ�Ա���� 
	void input(int flag); //�������ʽ��flagָʾ������ǵ�һ�����ǵڶ�������ʽ  
	void output(); //�������ʽ 
	void plus(); //����ʽ���
	void minus(); //����ʽ���
	double calValue(double x); //�������ʽ��x����ֵ
	void derivative(); //�������ʽ�ĵ�����
	void mutiply(); //����ʽ��� 
};

#endif 
