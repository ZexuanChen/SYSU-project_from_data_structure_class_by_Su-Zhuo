#include <iostream>
#include <iomanip>
#include <vector>
#include "exprTree.h"
using namespace std;

vector<ExprTree> exprs; //已经存在的表达式

void show() //打印已有表达式 
{
	cout << setw(100) << setfill('-') << "" << setfill(' ') << '\n' << "**目前已经存在的表达式**\n";
	cout << setw(7) << "序号" << "表达式\n"; 
	for (int i = 0; i < exprs.size(); i++) {
		cout << setw(7) << i+1 << exprs[i].GetExpr() << '\n';
	}
} 

int main()
{
	cout << left; //设置输出格式 	
	cout << "-----------------------------------------------------------" << endl
	     << "*******************欢迎使用表达式类型工具******************" << endl 
	     << "-----------------------------------------------------------" << endl
	     << "***        支持以下操作，交互时请输入相应操作序号：     ***" << endl
	     << "***                                                     ***" << endl
	     << "***        1、输入一个新的前缀表达式                    ***" << endl
	     << "***        2、查询已有表达式                            ***" << endl
	     << "***        3、中缀输出表达式                            ***" << endl
	     << "***        4、变量赋值                                  ***" << endl
	     << "***        5、表达式求值                                ***" << endl
	     << "***        6、合并两个表达式                            ***" << endl
	     << "***        7、合并常数项                                ***" << endl
	     << "***        8、退出                                      ***" << endl
	     << "-----------------------------------------------------------" << endl
	     << "***                      输入规则                       ***" << endl
	     << "***        1、表达式输入支持二元运算符+-*/^，变量(a-z)，***" << endl
	     << "***           非负常数（整型）。                        ***" << endl 
	     << "***        2、输出表达式时需要给出表达式序号。          ***" << endl
	     << "***        3、变量赋值时给出变量和值，用空格隔开。      ***" << endl
	     << "***        4、表达式求值时给出表达式序号。              ***" << endl
	     << "***        5、合并表达式时要给出运算符、两个表达式的    ***" << endl
	     << "***           序号，用空格隔开。                        ***" << endl
	     << "-----------------------------------------------------------" << endl
	     << "***                    祝您使用愉快！                   ***" << endl
	     << "-----------------------------------------------------------" << endl;
	
	
	bool flag = false;
	while (!flag) {
		int opt;
		cout << "\n请输入您要进行的操作的序号：";
		cin >> opt;
		getchar();
		if (opt < 1 || opt > 8) {
			cout << "输入无效！！";
			continue; 
		}
		
		ExprTree new_expr;
		char ch;
		int n;
		bool tag = false;
		switch (opt) {
			case 1: //输入表达式 
				while (!new_expr.ReadExpr()) { //强制合法 
					cout << "输入表达式不合法，请重新输入！\n";
				}
				
				//判断是否已经添加过该表达式 
				for (auto & it : exprs) {
					if (it.GetExpr() == new_expr.GetExpr()) {
						cout << "该表达式已存在！\n";
						tag = true; 
					}
				}
				if (tag) break;
				exprs.push_back(new_expr);
				cout << "添加成功！按2查询已有表达式\n"; 
				break; 
			case 2: 
				show(); //显示已有的表达式 
				break;
			case 3: //中缀输出 
				cout << "请输入表达式序号：";
				cin >> n;
				
				cout << '(' << exprs[n-1].GetExpr() << ')' << '\n';
				cout << "中缀输出为：";
				exprs[n-1].WriteExpr(exprs[n-1].GetRoot()); //中缀输出 
				cout << endl;
				break;
			case 4: //变量赋值
				cout << "请输入变量名和你要赋的值：";
				cin >> ch >> n;
				cg[ch-'a'] = n;
				break;
			case 5: //求值 
				cout << "请输入表达式序号：";
				cin >> n;
				
				cout << '(' << exprs[n-1].GetExpr() << ')' << '\n';
				cout << "表达式的值为：" << exprs[n-1].GetVal(exprs[n-1].GetRoot()) << '\n';
				break;
			case 6: //合并表达式 
				cout << "为实现合并，请给出运算符和两个表达式的序号：";
				char opt;
				int n1, n2;
				cin >> opt >> n1 >> n2;

				new_expr.CompoundExpr(opt, exprs[n1-1], exprs[n2-1]);
				exprs.push_back(new_expr);
				
				cout << "添加成功！按2查询已有表达式\n";
				break;
			case 7: //合并常数
				cout << "请输入表达式序号：";
				cin >> n;
				exprs[n-1].MergeConstIntro();
				cout << "表达式已更新！按2查询已有表达式\n";
				break; 
			case 8: //退出 
				flag = true;
				break;
			default:
				break;
		}
		
		if (flag) {
			cout << setw(100) << setfill('-') << "" << '\n' << "谢谢您的使用！下次再见~\n";
			cout << setw(100) << "";
			break;
		}
	}
}
