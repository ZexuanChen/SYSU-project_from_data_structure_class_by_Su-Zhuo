#include <iostream>
#include <iomanip>
#include <vector>
#include "ALGraph.h"
using namespace std;

int main()
{
	cout << right; //���������ʽ
	cout << "-----------------------------------------------------------" << endl
	     << "********************��ӭʹ��ͼ�ı�������*******************" << endl 
	     << "-----------------------------------------------------------" << endl
	     << "***   ������һ������ͼ��һ�����ڵ㣬 Ȼ��������Ӧ����   ***" << endl
	     << "***                                                     ***" << endl
	     << "***       1�����������ȱ����ĵ����кͱ߼�             ***" << endl
	     << "***       2�����������ȱ����ĵ����кͱ߼�             ***" << endl
	     << "***       3�����������ȱ�����                         ***" << endl
	     << "***       4�����������ȱ�����                         ***" << endl
	     << "***       5���˳�����                                   ***" << endl
	     << "-----------------------------------------------------------" << endl
	     << "***                   ����ͼ�������                    ***" << endl
	     << "***      ��һ������n m root����ʾ������������߱�����   ***" << endl
	     << "***      ���ڵ㣬����m�о�����u v����ʾһ�������       ***" << endl 
	     << "***    ��ע��<u, v>��<v, u>��ʾһ���ߣ������ظ�����     ***" << endl 
	     << "-----------------------------------------------------------" << endl
	     << "***                    ף��ʹ����죡                   ***" << endl
	     << "-----------------------------------------------------------" << endl;
	
	int n, m, u, v, root;

	cout << "������һ������ͼ��\n";
	cin >> n >> m >> root;
	ALGraph graph(n, m, root); //����ͼ
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		graph.add_edge(u, v); //Ĭ�ϼ�������
	}

	bool flag = false;
	while (!flag) {
		int opt;
		cout << "\n��������Ҫ���еĲ�������ţ�";
		cin >> opt;

		//��ǿ³����
		while (opt < 1 || opt > 5) {
			cout << "������Ч����\n";
			cout << "\n��������Ҫ���еĲ�������ţ�";
			cin >> opt;
		}

		switch (opt) {
            case 1:
				graph.dfs();
				graph.print_result();
				break;
            case 2:
				graph.bfs();
				graph.print_result();
				break;
            case 3:
				graph.dfs();
				graph.print_result_tree();
				break;
            case 4:
				graph.bfs();
				graph.print_result_tree();
				break;                
            case 5:
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