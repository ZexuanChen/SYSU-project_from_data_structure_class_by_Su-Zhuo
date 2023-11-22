//�ڽӶ��ر�Ķ���
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
    ALGraph(int n = 0, int m = 0, int t_root = 0); //���캯��
    ~ALGraph() {} //��������
    
    void add_edge(int u, int v);        //����
    void dfs();                         //�����������
    void bfs();                         //�����������
    void print_result();                //�����������кͱ߼�
    void print_result_tree();           //���������������
    void print_tree(int n, int depth);  //�����
private:
    vector<int> edge[MaxVexNum];        //�ڽӱ�
    int vex_num, edge_num, root;        //ͼ�Ķ������������������ĸ��ڵ�

    vector<int> tree[MaxVexNum];        //������Ȼ������ȱ�����������
    vector<int> seq;                    //�����ĵ�����
    vector<pair<int, int>> eg;          //�����ı߼�
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
    //����������
    edge[u].push_back(v);
    edge[v].push_back(u);
}

void ALGraph::dfs()
{
    //������д�Ž��������
    seq.clear();
    eg.clear();
    memset(tree, 0, sizeof tree);

    vector<bool> mark(MaxVexNum);
    MyStack stack;

    int p = root;
    mark[p] = true;
    seq.push_back(p);
    //�ǵݹ����ͼ
    while (p != 0 || !stack.isEmpty()) {
        int tmp = 0;

        /*p������һ��δ��ǵ��ڽӵ���Ϊ��һ�α�����p��Ȼ����
        ��pû�пɱ������ڽӵ㣬��ֵΪ0*/
        int i;
        for (i = 0; i < edge[p].size(); i++) {
            if (!mark[edge[p][i]]) {
                mark[edge[p][i]] = true;
                stack.push(p); //��ջ
                seq.push_back(edge[p][i]); //���������
                eg.push_back({p, edge[p][i]}); //����߼�
                tree[p].push_back(edge[p][i]);
                tmp = edge[p][i];
                break;
            }
        }
        p = tmp;
        
        //��pû�пɷ��ʵ��ڽӽڵ�ջ�л����нڵ㣬���������ջ�еĽڵ�
        if (p == 0 && !stack.isEmpty()) {
            p = stack.get_top();
            stack.pop();
        }
    }
}

void ALGraph::bfs()
{
    //������д�Ž��������
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
            if (!mark[edge[tp][i]]) { //���ڽӵ�֮ǰû�б�������
                mark[edge[tp][i]] = true;
                q.push(edge[tp][i]);
                eg.push_back({tp, edge[tp][i]});
                tree[tp].push_back(edge[tp][i]);
            }
        }
    }
}

//������������ͱ߼���
void ALGraph::print_result()
{
    //����㼯
    cout << "��ķ������У�\n";
    for (auto it : seq) {
        cout << it << ' ';
    }
    cout << '\n';

    //����߼�
    cout << "�߼���\n";
    for (auto it : eg) {
        cout << it.first << ' ' << it.second << '\n';
    }
}

void ALGraph::print_result_tree()
{
    print_tree(root, 0);
}

//�����
void ALGraph::print_tree(int n, int depth)
{
    cout << setw(depth*5) << n << '\n';
    for (int i = 0; i < tree[n].size(); i++) {
        print_tree(tree[n][i], depth+1);
    }
}

#endif