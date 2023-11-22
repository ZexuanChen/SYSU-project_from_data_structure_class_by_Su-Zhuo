#include "polyCalculator.h"
#include "polyCalculator.cpp"

int main()
{
	polyCalculator calculator;
	cout << "-----------------------------------------------------------" << endl;
	cout << "*****************欢迎使用简易多项式计算器******************" << endl;
	cout << "***                                                     ***" << endl;
	cout << "***                  你可以实现的功能：                 ***" << endl;
	cout << "***                   1.多项式相加                      ***" << endl;
	cout << "***                   2.多项式相减                      ***" << endl;
	cout << "***                   3.多项式相乘                      ***" << endl;
	cout << "***                   4.多项式在x处的值                 ***" << endl;
	cout << "***                   5.多项式的导函数                  ***" << endl;
	cout << "***                   6.退出计算器                      ***" << endl;
	cout << "***                                                     ***" << endl;
	cout << "***                  多项式输入规则：                   ***" << endl;
	cout << "***    输入一行n c1 e1 c2 e2 ... cn en，其中n为项数，   ***" << endl;
	cout << "***           ci、ei分别为第i项的系数、指数             ***" << endl;
	cout << "***                                                     ***" << endl;
	cout << "***                  多项式输出规则：                   ***" << endl;
	cout << "***     以带x的多项式形式升序输出，如2x^-1 - 4 + 3x^1   ***" << endl;
	cout << "***                                                     ***" << endl;
	cout << "***                     注意事项：                      ***" << endl;
	cout << "***   先选择你要实现的功能的序号，再按指示输入多项式    ***" << endl;
	cout << "-----------------------------------------------------------" << endl; 
	
	int opt;
	bool flag = false;
	while (1) {
		if (flag) break;
		cout << "请选择你需要实现的功能的序号：";
		cin >> opt;
		calculator.clear(); //清空 
		 
		switch (opt) {
		case 1: 
			cout << "请输入第一个多项式：";
			calculator.input(0);
			cout << "请输入第二个多项式：";
			calculator.input(1);
			calculator.plus();
			cout << "结果为："; 
			calculator.output();
			break;
		case 2: 
			cout << "请输入第一个多项式：";
			calculator.input(0);
			cout << "请输入第二个多项式：";
			calculator.input(1);
			calculator.minus();
			cout << "结果为：";
			calculator.output();
			break;
		case 3: 
			cout << "请输入第一个多项式：";
			calculator.input(0);
			cout << "请输入第二个多项式：";
			calculator.input(1);
			calculator.mutiply();
			cout << "结果为：";
			calculator.output();
			break;
		case 4: 
			double x;
			cout << "请输入多项式："; 
			calculator.input(0);
			cout << "请输入x的值：";
			cin >> x; 
			cout << "该多项式在x=" << x << "处的值为：" << calculator.calValue(x) << endl;
			break;
		case 5: 
			cout << "请输入多项式："; 
			calculator.input(0);
			calculator.derivative();
			cout << "该多项式的导函数为：";
			calculator.output(); 
			break;
		case 6: 
			cout << "-----------------------------------------------------------" << endl;
			cout << "*******************感谢您的使用，再见！********************" << endl;
			flag = true;
			break; 
		default:
			cout << "无效输入！\n";
			break;
        }
	}
}
