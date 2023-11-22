#include <iostream>
#include <iomanip>
#include <vector>
#include "ALGraph.h"
using namespace std;

int main()
{
	cout << right; //设置输出格式
	cout << "-----------------------------------------------------------" << endl
	     << "********************欢迎使用图的遍历程序*******************" << endl 
	     << "-----------------------------------------------------------" << endl
	     << "***   请输入一个无向图和一个根节点， 然后输入相应操作   ***" << endl
	     << "***                                                     ***" << endl
	     << "***       1、输出深度优先遍历的点序列和边集             ***" << endl
	     << "***       2、输出广度优先遍历的点序列和边集             ***" << endl
	     << "***       3、输出深度优先遍历树                         ***" << endl
	     << "***       4、输出广度优先遍历树                         ***" << endl
	     << "***       5、退出程序                                   ***" << endl
	     << "-----------------------------------------------------------" << endl
	     << "***                   无向图输入规则                    ***" << endl
	     << "***      第一行输入n m root，表示顶点数、无向边边数、   ***" << endl
	     << "***      根节点，后面m行均输入u v，表示一条无向边       ***" << endl 
	     << "***    ！注：<u, v>和<v, u>表示一条边，不用重复输入     ***" << endl 
	     << "-----------------------------------------------------------" << endl
	     << "***                    祝您使用愉快！                   ***" << endl
	     << "-----------------------------------------------------------" << endl;
	
	int n, m, u, v, root;

	cout << "请输入一个无向图：\n";
	cin >> n >> m >> root;
	ALGraph graph(n, m, root); //构造图
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		graph.add_edge(u, v); //默认加两条边
	}

	bool flag = false;
	while (!flag) {
		int opt;
		cout << "\n请输入您要进行的操作的序号：";
		cin >> opt;

		//增强鲁棒性
		while (opt < 1 || opt > 5) {
			cout << "输入无效！！\n";
			cout << "\n请输入您要进行的操作的序号：";
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
			cout << setw(30) << setfill('-') << "\n" << "谢谢您的使用！下次再见~\n";
			break;
		}
	}
}