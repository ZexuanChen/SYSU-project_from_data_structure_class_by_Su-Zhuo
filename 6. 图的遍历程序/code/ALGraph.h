//邻接多重表的定义
#ifndef ALGraph_h
#define ALGraph_h
#define MaxVexNum 500
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <utility>
#include <iomanip>
#include "stack.h"
using namespace std;

typedef Stack<int> MyStack;

class ALGraph {
public:
    ALGraph(int n = 0, int m = 0, int t_root = 0); //构造函数
    ~ALGraph() {} //析构函数
    
    void add_edge(int u, int v);        //建边
    void dfs();                         //深度优先搜索
    void bfs();                         //广度优先搜索
    void print_result();                //输出点访问序列和边集
    void print_result_tree();           //调用输出树主函数
    void print_tree(int n, int depth);  //输出树
private:
    vector<int> edge[MaxVexNum];        //邻接表
    int vex_num, edge_num, root;        //图的顶点数、边数、给定的根节点

    vector<int> tree[MaxVexNum];        //深度优先或广度优先遍历建的新树
    vector<int> seq;                    //搜索的点序列
    vector<pair<int, int>> eg;          //搜索的边集
};

ALGraph::ALGraph(int n, int m, int t_root)
{
    vex_num = n, edge_num = m, root = t_root;

    for (int i = 1; i <= n; i++) {
        edge[i].clear();
    }
}

void ALGraph::add_edge(int u, int v)
{
    //新增两条边
    edge[u].push_back(v);
    edge[v].push_back(u);
}

void ALGraph::dfs()
{
    //清空所有存放结果的容器
    seq.clear();
    eg.clear();
    memset(tree, 0, sizeof tree);

    vector<bool> mark(MaxVexNum);
    MyStack stack;

    int p = root;
    mark[p] = true;
    seq.push_back(p);
    //非递归遍历图
    while (p != 0 || !stack.isEmpty()) {
        int tmp = 0;

        /*p的任意一个未标记的邻接点作为下一次遍历的p，然后标记
        若p没有可遍历的邻接点，则赋值为0*/
        int i;
        for (i = 0; i < edge[p].size(); i++) {
            if (!mark[edge[p][i]]) {
                mark[edge[p][i]] = true;
                stack.push(p); //入栈
                seq.push_back(edge[p][i]); //加入点序列
                eg.push_back({p, edge[p][i]}); //加入边集
                tree[p].push_back(edge[p][i]);
                tmp = edge[p][i];
                break;
            }
        }
        p = tmp;
        
        //若p没有可访问的邻接节但栈中还留有节点，则继续遍历栈中的节点
        if (p == 0 && !stack.isEmpty()) {
            p = stack.get_top();
            stack.pop();
        }
    }
}

void ALGraph::bfs()
{
    //清空所有存放结果的容器
    seq.clear();
    eg.clear();
    memset(tree, 0, sizeof tree);

    vector<bool> mark(MaxVexNum);
    queue<int> q;
    q.push(root);
    mark[root] = true;

    while (!q.empty()) {
        int tp = q.front();
        q.pop();
        seq.push_back(tp);

        for (int i = 0; i < edge[tp].size(); i++) {
            if (!mark[edge[tp][i]]) { //若邻接点之前没有被遍历过
                mark[edge[tp][i]] = true;
                q.push(edge[tp][i]);
                eg.push_back({tp, edge[tp][i]});
                tree[tp].push_back(edge[tp][i]);
            }
        }
    }
}

//输出结果（点序和边集）
void ALGraph::print_result()
{
    //输出点集
    cout << "点的访问序列：\n";
    for (auto it : seq) {
        cout << it << ' ';
    }
    cout << '\n';

    //输出边集
    cout << "边集：\n";
    for (auto it : eg) {
        cout << it.first << ' ' << it.second << '\n';
    }
}

void ALGraph::print_result_tree()
{
    print_tree(root, 0);
}

//输出树
void ALGraph::print_tree(int n, int depth)
{
    cout << setw(depth*5) << n << '\n';
    for (int i = 0; i < tree[n].size(); i++) {
        print_tree(tree[n][i], depth+1);
    }
}

#endif