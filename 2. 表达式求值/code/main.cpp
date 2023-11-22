#include <iostream>
#include <iomanip>
#include "calculator.h"
#include "calculator.cpp"
using namespace std;

int main()
{
    Calculator calculator1;
	cout << "-----------------------------------------------------------" << endl;
	cout << "*******************欢迎使用简易计算器**********************" << endl;
	cout << "***                                                     ***" << endl;
	cout << "***     支持输入的运算符：+、-、*、/、(、)、^，其中     ***" << endl;
	cout << "***                     ^代表乘方                       ***" << endl;
	cout << "***                                                     ***" << endl;
	cout << "***                 ！！退出请输入：q                   ***" << endl;
	cout << "***                   祝您使用愉快！                    ***" << endl;
	cout << "-----------------------------------------------------------" << endl; 
	
	while (1) {
		calculator1.clear();
		string s;
		cout << "请输入表达式：";
		cin >> s;
		if (s == "q") {
			cout << "-----------------------------------------------------------" << endl;
			cout << "*******************感谢您的使用，再见！********************" << endl;
			break;
		}
		else {
			calculator1.getS(s);
			calculator1.eval();
			cout << setfill('-') << setw(100) << "" << '\n'; 
			cout << "计算结果为：" << calculator1.getRes() << "\n\n";
		}
	} 
}
