#ifndef polyCalculator_H
#define polyCalculator_H
#define PII pair<double, double>//first为指数，second为系数 
#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;

//简易多项式计算器类
class polyCalculator {
	vector<PII> poly[2], res; //vector中元素为 (指数，系数)对，统一用两个vector容器存储输入多项式，用一个vector容器存储输出多项式
	
public:
	polyCalculator(); //构造函数 
	~polyCalculator(); //析构函数
	void clear(); //清空成员函数 
	void input(int flag); //输入多项式，flag指示输入的是第一个还是第二个多项式  
	void output(); //输出多项式 
	void plus(); //多项式相加
	void minus(); //多项式相减
	double calValue(double x); //计算多项式在x处的值
	void derivative(); //计算多项式的导函数
	void mutiply(); //多项式相乘 
};

#endif 
