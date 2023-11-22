#include "imgProcess.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	cout << left;
	cout << "-----------------------------------------------------------" << endl
		<< "******************��ӭʹ�ü���ͼ�������*****************" << endl
		<< "-----------------------------------------------------------" << endl
		<< "***        ֧�����²���������ʱ��������Ӧ������ţ�     ***" << endl
		<< "***                                                     ***" << endl
		<< "***          1������ͼƬ                                ***" << endl
		<< "***          2����ʾͼƬ                                ***" << endl
		<< "***          3��תΪ�Ҷ�ͼ                              ***" << endl
		<< "***          4���ı��С                                ***" << endl
		<< "***          5��ѹ��ͼƬ                                ***" << endl
		<< "***          6����ѹ��                                  ***" << endl
		<< "***          7���˳�                                    ***" << endl
		<< "-----------------------------------------------------------" << endl
		<< "***                    ף��ʹ����죡                   ***" << endl
		<< "-----------------------------------------------------------" << endl;

	bool flag = false;
	int opt;
	ImgProcess imgp;

	while (1) {
		cout << "�����������ţ�";
		cin >> opt;

		string s;
		int h, w;
		switch (opt) {
		case 1:
			cout << "������ͼƬ����";
			cin >> s;
			imgp.clear();
			while (!imgp.img_read(s)) {
				cout << "���ļ������ڣ����������룡\n";
				cout << "������ͼƬ����";
				cin >> s;
			}
			break;
		case 2:
			imgp.img_show();
			break;
		case 3:
			imgp.img_color_to_gray();
			break;
		case 4:
			cout << "�������µĴ�С�������߶ȣ���";
			cin >> w >> h;
			imgp.resize(w, h);
			break;
		case 5:
			imgp.encode();
			break;
		case 6:
			cout << "������ѹ���ļ�����";
			cin >> s;
			imgp.decode(s);
			break;
		case 7:
			flag = true;
			break;
		default:
			cout << "������Ч����\n";
			break;
		}

		if (flag) {
			cout << setw(30) << setfill('-') << "" << '\n' << "|| лл����ʹ�ã��´��ټ�~ ||\n";
			break;
		}
	}
}