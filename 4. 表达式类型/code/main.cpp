#include <iostream>
#include <iomanip>
#include <vector>
#include "exprTree.h"
using namespace std;

vector<ExprTree> exprs; //�Ѿ����ڵı��ʽ

void show() //��ӡ���б��ʽ 
{
	cout << setw(100) << setfill('-') << "" << setfill(' ') << '\n' << "**Ŀǰ�Ѿ����ڵı��ʽ**\n";
	cout << setw(7) << "���" << "���ʽ\n"; 
	for (int i = 0; i < exprs.size(); i++) {
		cout << setw(7) << i+1 << exprs[i].GetExpr() << '\n';
	}
} 

int main()
{
	cout << left; //���������ʽ 	
	cout << "-----------------------------------------------------------" << endl
	     << "*******************��ӭʹ�ñ��ʽ���͹���******************" << endl 
	     << "-----------------------------------------------------------" << endl
	     << "***        ֧�����²���������ʱ��������Ӧ������ţ�     ***" << endl
	     << "***                                                     ***" << endl
	     << "***        1������һ���µ�ǰ׺���ʽ                    ***" << endl
	     << "***        2����ѯ���б��ʽ                            ***" << endl
	     << "***        3����׺������ʽ                            ***" << endl
	     << "***        4��������ֵ                                  ***" << endl
	     << "***        5�����ʽ��ֵ                                ***" << endl
	     << "***        6���ϲ��������ʽ                            ***" << endl
	     << "***        7���ϲ�������                                ***" << endl
	     << "***        8���˳�                                      ***" << endl
	     << "-----------------------------------------------------------" << endl
	     << "***                      �������                       ***" << endl
	     << "***        1�����ʽ����֧�ֶ�Ԫ�����+-*/^������(a-z)��***" << endl
	     << "***           �Ǹ����������ͣ���                        ***" << endl 
	     << "***        2��������ʽʱ��Ҫ�������ʽ��š�          ***" << endl
	     << "***        3��������ֵʱ����������ֵ���ÿո������      ***" << endl
	     << "***        4�����ʽ��ֵʱ�������ʽ��š�              ***" << endl
	     << "***        5���ϲ����ʽʱҪ������������������ʽ��    ***" << endl
	     << "***           ��ţ��ÿո������                        ***" << endl
	     << "-----------------------------------------------------------" << endl
	     << "***                    ף��ʹ����죡                   ***" << endl
	     << "-----------------------------------------------------------" << endl;
	
	
	bool flag = false;
	while (!flag) {
		int opt;
		cout << "\n��������Ҫ���еĲ�������ţ�";
		cin >> opt;
		getchar();
		if (opt < 1 || opt > 8) {
			cout << "������Ч����";
			continue; 
		}
		
		ExprTree new_expr;
		char ch;
		int n;
		bool tag = false;
		switch (opt) {
			case 1: //������ʽ 
				while (!new_expr.ReadExpr()) { //ǿ�ƺϷ� 
					cout << "������ʽ���Ϸ������������룡\n";
				}
				
				//�ж��Ƿ��Ѿ���ӹ��ñ��ʽ 
				for (auto & it : exprs) {
					if (it.GetExpr() == new_expr.GetExpr()) {
						cout << "�ñ��ʽ�Ѵ��ڣ�\n";
						tag = true; 
					}
				}
				if (tag) break;
				exprs.push_back(new_expr);
				cout << "��ӳɹ�����2��ѯ���б��ʽ\n"; 
				break; 
			case 2: 
				show(); //��ʾ���еı��ʽ 
				break;
			case 3: //��׺��� 
				cout << "��������ʽ��ţ�";
				cin >> n;
				
				cout << '(' << exprs[n-1].GetExpr() << ')' << '\n';
				cout << "��׺���Ϊ��";
				exprs[n-1].WriteExpr(exprs[n-1].GetRoot()); //��׺��� 
				cout << endl;
				break;
			case 4: //������ֵ
				cout << "���������������Ҫ����ֵ��";
				cin >> ch >> n;
				cg[ch-'a'] = n;
				break;
			case 5: //��ֵ 
				cout << "��������ʽ��ţ�";
				cin >> n;
				
				cout << '(' << exprs[n-1].GetExpr() << ')' << '\n';
				cout << "���ʽ��ֵΪ��" << exprs[n-1].GetVal(exprs[n-1].GetRoot()) << '\n';
				break;
			case 6: //�ϲ����ʽ 
				cout << "Ϊʵ�ֺϲ����������������������ʽ����ţ�";
				char opt;
				int n1, n2;
				cin >> opt >> n1 >> n2;

				new_expr.CompoundExpr(opt, exprs[n1-1], exprs[n2-1]);
				exprs.push_back(new_expr);
				
				cout << "��ӳɹ�����2��ѯ���б��ʽ\n";
				break;
			case 7: //�ϲ�����
				cout << "��������ʽ��ţ�";
				cin >> n;
				exprs[n-1].MergeConstIntro();
				cout << "���ʽ�Ѹ��£���2��ѯ���б��ʽ\n";
				break; 
			case 8: //�˳� 
				flag = true;
				break;
			default:
				break;
		}
		
		if (flag) {
			cout << setw(100) << setfill('-') << "" << '\n' << "лл����ʹ�ã��´��ټ�~\n";
			cout << setw(100) << "";
			break;
		}
	}
}
