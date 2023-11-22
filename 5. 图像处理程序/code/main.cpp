#include "imgProcess.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	cout << left;
	cout << "-----------------------------------------------------------" << endl
		<< "******************欢迎使用简易图像处理程序*****************" << endl
		<< "-----------------------------------------------------------" << endl
		<< "***        支持以下操作，交互时请输入相应操作序号：     ***" << endl
		<< "***                                                     ***" << endl
		<< "***          1、输入图片                                ***" << endl
		<< "***          2、显示图片                                ***" << endl
		<< "***          3、转为灰度图                              ***" << endl
		<< "***          4、改变大小                                ***" << endl
		<< "***          5、压缩图片                                ***" << endl
		<< "***          6、解压缩                                  ***" << endl
		<< "***          7、退出                                    ***" << endl
		<< "-----------------------------------------------------------" << endl
		<< "***                    祝您使用愉快！                   ***" << endl
		<< "-----------------------------------------------------------" << endl;

	bool flag = false;
	int opt;
	ImgProcess imgp;

	while (1) {
		cout << "请输入操作序号：";
		cin >> opt;

		string s;
		int h, w;
		switch (opt) {
		case 1:
			cout << "请输入图片名：";
			cin >> s;
			imgp.clear();
			while (!imgp.img_read(s)) {
				cout << "该文件不存在，请重新输入！\n";
				cout << "请输入图片名：";
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
			cout << "请输入新的大小（宽度与高度）：";
			cin >> w >> h;
			imgp.resize(w, h);
			break;
		case 5:
			imgp.encode();
			break;
		case 6:
			cout << "请输入压缩文件名：";
			cin >> s;
			imgp.decode(s);
			break;
		case 7:
			flag = true;
			break;
		default:
			cout << "输入无效！！\n";
			break;
		}

		if (flag) {
			cout << setw(30) << setfill('-') << "" << '\n' << "|| 谢谢您的使用！下次再见~ ||\n";
			break;
		}
	}
}