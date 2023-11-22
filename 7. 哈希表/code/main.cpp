#include <iostream>
#include <iomanip>
#include <vector>
#include "hash_table.h"
#define TYPE 0 //0����ʹ��α������з������ϣ��ͻ��1����ƽ��̽�ⷨ 
using namespace std;

int main()
{
	cout << left; //���������ʽ
	cout << "-----------------------------------------------------------" << endl
	     << "***********************��ӭʹ�ù�ϣ��**********************" << endl 
	     << "-----------------------------------------------------------" << endl
	     << "***                        ����ԣ�                     ***" << endl
	     << "***                   1������һ������                   ***" << endl
	     << "***                   2��ɾ��һ������                   ***" << endl
	     << "***                   3����ӡ��ϣ��                     ***" << endl
	     << "***                   4���˳�����                       ***" << endl
	     << "***                 ������������Ӧ�������              ***" << endl
	     << "-----------------------------------------------------------" << endl
	     << "***                    ף��ʹ����죡                   ***" << endl
	     << "-----------------------------------------------------------" << endl;
	
	bool flag = false;
	HashTable tb;
	 
	while (!flag) {
		int opt;
		cout << "\n��������Ҫ���еĲ�������ţ�";
		cin >> opt;

		//��ǿ³����
		while (opt < 1 || opt > 4) {
			cout << "������Ч����\n";
			cout << "\n��������Ҫ���еĲ�������ţ�";
			cin >> opt;
		}
		getchar(); //��ֹ�����getline������ 
		
		string name;
		int value;
		switch (opt) {
            case 1:
				cout << "���������֣�";
				getline(cin, name);
				if (tb.insert(name, TYPE)) cout << "����ɹ���\n";
				else cout << "����ʧ�ܣ�\n"; 
				break;
            case 2:
				cout << "���������֣�";
				getline(cin, name);
				if (tb.remove(name, TYPE)) cout << "ɾ���ɹ���\n";
				else cout << "ɾ��ʧ�ܣ������ֲ����ڣ�\n";
				break;
            case 3:
				tb.print();
				break; 
			case 4:
				flag = true;
				break;               
            default:
                break;
		} 
		
		if (flag) {
			cout << setw(30) << setfill('-') << "\n" << "лл����ʹ�ã��´��ټ�~\n";
			break;
		}
	}
}
