#include <iostream>
#include <iomanip>
#include "textAnaTool.h"
#include "textAnaTool.cpp"
using namespace std;

int main()
{
	cout << left; //���������ʽ 
	TextAnaTool tool;	
	cout << "-----------------------------------------------------------" << endl
	     << "*******************��ӭʹ���ı���������********************" << endl 
	     << "***                                                     ***" << endl
	     << "***    ����ͳ�ƴʻ����ı��еĳ��ִ������״γ��ֵ��к�   ***" << endl
	     << "***                                                     ***" << endl
	     << "***         �����������ļ������ʻ�������ʻ㼯          ***" << endl
	     << "***               **���ÿո񽫴ʻ�ֿ�**                ***" << endl
	     << "-----------------------------------------------------------" << endl
	     << "***              �˳����������ļ���ʱ����q              ***" << endl
	     << "-----------------------------------------------------------" << endl
	     << "***                    ף��ʹ����죡                   ***" << endl
	     << "-----------------------------------------------------------" << endl;
	     
	bool flag = false;
	while (1) {
		tool.clear();
		string textName;
		cout << "�������ļ�����";
		cin >> textName;
		//�����ļ�����ʧ�ܺ��˳������ 
		while (1) {
			if (textName == "q") {
				flag = true;
				break;
			}
			else if (tool.buildStream(textName)) {
				break;
			}
			else {
				cout << "���������ļ����������������룡��\n";
				cout << "�������ļ�����";
				cin >> textName;
			}
		}
		
		if (flag) {
			cout << setw(100) << setfill('-') << "" << '\n' << "лл����ʹ�ã��´��ټ�~\n";
			cout << setw(100) << "";
			break;
		}
		
		tool.readWords();
		tool.analyse();
	}
}
