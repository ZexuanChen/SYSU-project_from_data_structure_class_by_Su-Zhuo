#include "polyCalculator.h"
#include "polyCalculator.cpp"

int main()
{
	polyCalculator calculator;
	cout << "-----------------------------------------------------------" << endl;
	cout << "*****************��ӭʹ�ü��׶���ʽ������******************" << endl;
	cout << "***                                                     ***" << endl;
	cout << "***                  �����ʵ�ֵĹ��ܣ�                 ***" << endl;
	cout << "***                   1.����ʽ���                      ***" << endl;
	cout << "***                   2.����ʽ���                      ***" << endl;
	cout << "***                   3.����ʽ���                      ***" << endl;
	cout << "***                   4.����ʽ��x����ֵ                 ***" << endl;
	cout << "***                   5.����ʽ�ĵ�����                  ***" << endl;
	cout << "***                   6.�˳�������                      ***" << endl;
	cout << "***                                                     ***" << endl;
	cout << "***                  ����ʽ�������                   ***" << endl;
	cout << "***    ����һ��n c1 e1 c2 e2 ... cn en������nΪ������   ***" << endl;
	cout << "***           ci��ei�ֱ�Ϊ��i���ϵ����ָ��             ***" << endl;
	cout << "***                                                     ***" << endl;
	cout << "***                  ����ʽ�������                   ***" << endl;
	cout << "***     �Դ�x�Ķ���ʽ��ʽ�����������2x^-1 - 4 + 3x^1   ***" << endl;
	cout << "***                                                     ***" << endl;
	cout << "***                     ע�����                      ***" << endl;
	cout << "***   ��ѡ����Ҫʵ�ֵĹ��ܵ���ţ��ٰ�ָʾ�������ʽ    ***" << endl;
	cout << "-----------------------------------------------------------" << endl; 
	
	int opt;
	bool flag = false;
	while (1) {
		if (flag) break;
		cout << "��ѡ������Ҫʵ�ֵĹ��ܵ���ţ�";
		cin >> opt;
		calculator.clear(); //��� 
		 
		switch (opt) {
		case 1: 
			cout << "�������һ������ʽ��";
			calculator.input(0);
			cout << "������ڶ�������ʽ��";
			calculator.input(1);
			calculator.plus();
			cout << "���Ϊ��"; 
			calculator.output();
			break;
		case 2: 
			cout << "�������һ������ʽ��";
			calculator.input(0);
			cout << "������ڶ�������ʽ��";
			calculator.input(1);
			calculator.minus();
			cout << "���Ϊ��";
			calculator.output();
			break;
		case 3: 
			cout << "�������һ������ʽ��";
			calculator.input(0);
			cout << "������ڶ�������ʽ��";
			calculator.input(1);
			calculator.mutiply();
			cout << "���Ϊ��";
			calculator.output();
			break;
		case 4: 
			double x;
			cout << "���������ʽ��"; 
			calculator.input(0);
			cout << "������x��ֵ��";
			cin >> x; 
			cout << "�ö���ʽ��x=" << x << "����ֵΪ��" << calculator.calValue(x) << endl;
			break;
		case 5: 
			cout << "���������ʽ��"; 
			calculator.input(0);
			calculator.derivative();
			cout << "�ö���ʽ�ĵ�����Ϊ��";
			calculator.output(); 
			break;
		case 6: 
			cout << "-----------------------------------------------------------" << endl;
			cout << "*******************��л����ʹ�ã��ټ���********************" << endl;
			flag = true;
			break; 
		default:
			cout << "��Ч���룡\n";
			break;
        }
	}
}
