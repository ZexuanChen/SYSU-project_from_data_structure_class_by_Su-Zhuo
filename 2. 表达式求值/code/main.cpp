#include <iostream>
#include <iomanip>
#include "calculator.h"
#include "calculator.cpp"
using namespace std;

int main()
{
    Calculator calculator1;
	cout << "-----------------------------------------------------------" << endl;
	cout << "*******************��ӭʹ�ü��׼�����**********************" << endl;
	cout << "***                                                     ***" << endl;
	cout << "***     ֧��������������+��-��*��/��(��)��^������     ***" << endl;
	cout << "***                     ^����˷�                       ***" << endl;
	cout << "***                                                     ***" << endl;
	cout << "***                 �����˳������룺q                   ***" << endl;
	cout << "***                   ף��ʹ����죡                    ***" << endl;
	cout << "-----------------------------------------------------------" << endl; 
	
	while (1) {
		calculator1.clear();
		string s;
		cout << "��������ʽ��";
		cin >> s;
		if (s == "q") {
			cout << "-----------------------------------------------------------" << endl;
			cout << "*******************��л����ʹ�ã��ټ���********************" << endl;
			break;
		}
		else {
			calculator1.getS(s);
			calculator1.eval();
			cout << setfill('-') << setw(100) << "" << '\n'; 
			cout << "������Ϊ��" << calculator1.getRes() << "\n\n";
		}
	} 
}
