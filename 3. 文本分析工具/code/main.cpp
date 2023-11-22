#include <iostream>
#include <iomanip>
#include "textAnaTool.h"
#include "textAnaTool.cpp"
using namespace std;

int main()
{
	cout << left; //设置输出格式 
	TextAnaTool tool;	
	cout << "-----------------------------------------------------------" << endl
	     << "*******************欢迎使用文本分析工具********************" << endl 
	     << "***                                                     ***" << endl
	     << "***    可以统计词汇在文本中的出现次数及首次出现的行号   ***" << endl
	     << "***                                                     ***" << endl
	     << "***         请依次输入文件名、词汇个数、词汇集          ***" << endl
	     << "***               **请用空格将词汇分开**                ***" << endl
	     << "-----------------------------------------------------------" << endl
	     << "***              退出请在输入文件名时输入q              ***" << endl
	     << "-----------------------------------------------------------" << endl
	     << "***                    祝您使用愉快！                   ***" << endl
	     << "-----------------------------------------------------------" << endl;
	     
	bool flag = false;
	while (1) {
		tool.clear();
		string textName;
		cout << "请输入文件名：";
		cin >> textName;
		//处理文件输入失败和退出的情况 
		while (1) {
			if (textName == "q") {
				flag = true;
				break;
			}
			else if (tool.buildStream(textName)) {
				break;
			}
			else {
				cout << "！！输入文件名错误，请重新输入！！\n";
				cout << "请输入文件名：";
				cin >> textName;
			}
		}
		
		if (flag) {
			cout << setw(100) << setfill('-') << "" << '\n' << "谢谢您的使用！下次再见~\n";
			cout << setw(100) << "";
			break;
		}
		
		tool.readWords();
		tool.analyse();
	}
}
