#include <iostream>
#include <iomanip>
#include <vector>
#include "hash_table.h"
#define TYPE 0 //0代表使用伪随机序列法解决哈希冲突，1代表平方探测法 
using namespace std;

int main()
{
	cout << left; //设置输出格式
	cout << "-----------------------------------------------------------" << endl
	     << "***********************欢迎使用哈希表**********************" << endl 
	     << "-----------------------------------------------------------" << endl
	     << "***                        你可以：                     ***" << endl
	     << "***                   1、插入一个名字                   ***" << endl
	     << "***                   2、删除一个名字                   ***" << endl
	     << "***                   3、打印哈希表                     ***" << endl
	     << "***                   4、退出程序                       ***" << endl
	     << "***                 交互请输入相应操作序号              ***" << endl
	     << "-----------------------------------------------------------" << endl
	     << "***                    祝您使用愉快！                   ***" << endl
	     << "-----------------------------------------------------------" << endl;
	
	bool flag = false;
	HashTable tb;
	 
	while (!flag) {
		int opt;
		cout << "\n请输入您要进行的操作的序号：";
		cin >> opt;

		//增强鲁棒性
		while (opt < 1 || opt > 4) {
			cout << "输入无效！！\n";
			cout << "\n请输入您要进行的操作的序号：";
			cin >> opt;
		}
		getchar(); //防止后面的getline出问题 
		
		string name;
		int value;
		switch (opt) {
            case 1:
				cout << "请输入名字：";
				getline(cin, name);
				if (tb.insert(name, TYPE)) cout << "插入成功！\n";
				else cout << "插入失败！\n"; 
				break;
            case 2:
				cout << "请输入名字：";
				getline(cin, name);
				if (tb.remove(name, TYPE)) cout << "删除成功！\n";
				else cout << "删除失败！改名字不存在！\n";
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
			cout << setw(30) << setfill('-') << "\n" << "谢谢您的使用！下次再见~\n";
			break;
		}
	}
}
