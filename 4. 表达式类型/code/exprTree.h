#ifndef ExprTree_H
#define ExprTree_H

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int cg[26]; //变量对应的值，初始值为0

//二叉树节点定义
struct Node {
	int flag; //flag = 1表示运算符，flag = 2表示常数，flag = 3表示变量
	union {
		char opt, var;
		int num;
	};
	Node *left, *right;
	
	Node() {
		flag = 2;
		num = 0;
		left = right = nullptr;
	}
};
	
class ExprTree {
public:
	ExprTree() { //构造函数，直接定义 
		root = nullptr;
		pos = 0;
		flag = false; 
	}
	~ExprTree() {} //析构函数 
	
	bool ReadExpr(); //读取前缀表达式
	Node* toTree(); //表达式转二叉树 
	void WriteExpr(Node*); //后缀输出表达式，适当加括号
	int GetVal(Node*); //求值
	void CompoundExpr(char opt, ExprTree E1, ExprTree E2); //合并两个表达式形成一个新的表达式
	void MergeConstIntro(); //合并常数项入口函数
	void MergeConst(Node*); //合并常数项 
	void UpdateExpr(Node*); //更新前缀表达式 
	Node* GetRoot(); //返回根节点 
	string GetExpr(); //返回表达式 
	
private:
	Node *root; //表达式树的根节点 
	string s; //前缀表达式
	int pos; //表达式转二叉树位置指针 
	bool flag; //输入合法性判断 
};

//读入前缀表达式 
bool ExprTree::ReadExpr() 
{
	cout << "请输入表达式：";
	getline(cin, s);
	
	flag = false;
	pos = 0;
	root = toTree();
	//前缀表达式合法性检测 
	for (; pos < s.size(); pos++) {
		if (s[pos] != ' ') {
			flag = true;
			break;
		}
	}
	
	if (flag) return false; //表达式不合法
	return true; 
}

//前缀表达式转化为表达式树 
Node* ExprTree::toTree()
{
	if (flag) return nullptr;

	//忽略空格 
	if (s[pos] == ' ') {
		pos++; 
		return toTree(); //向后走
	}
	//如果为整型常数 
	else if (s[pos] <= '9' && s[pos] >= '0') {
		int num = 0;
		while (pos < s.size() && s[pos] <= '9' && s[pos] >= '0') {
			num = num*10+s[pos]-'0';
			pos++;
		}
		Node* leap = new Node();
		leap->flag = 2, leap->num = num;
		return leap;
	}
	//如果为变量 
	else if (s[pos] <= 'z' && s[pos] >= 'a') {
		Node* leap = new Node();
		leap->flag = 3, leap->var = s[pos];
		pos++;
		return leap;
	}
	//如果为操作数
	else if (s[pos] == '+' || s[pos] == '-' || s[pos] == '*' || s[pos] == '/' || s[pos] == '^') {
		Node *now = new Node(); //创建节点 
		now->flag = 1, now->opt = s[pos];
		pos++;
		if (pos >= s.size()) { //合法性检测 
			flag = true;
			return nullptr;
		}
		now->left = toTree(); //递归左子树 
		if (pos >= s.size()) { //合法性检测 
			flag = true;
			return nullptr;
		}
		now->right = toTree(); //递归右子树
		return now; 
	} 
	else { //合法性检测 
		flag = true;
		return nullptr;
	}
}

//中缀形式输出表达式 
void ExprTree::WriteExpr(Node* now)
{
	//基线条件为变量或常数 
	if (now->flag == 2) {
		cout << now->num;
		return;
	}
	if (now->flag == 3) {
		cout << now->var;
		return;
	}
	
	//递归输出 
	if (now != root) cout << '(';
	WriteExpr(now->left); //左递归 
	
	cout << now->opt; //输出运算符 
	
	WriteExpr(now->right); //右递归
	if (now != root) cout << ')';
	return;
}

//求值
int ExprTree::GetVal(Node* now)
{
	//常数或变量 
	if (now->flag == 2) {
		return now->num;
	}
	if (now->flag == 3) {
		return cg[now->var-'a']; //变量转换为对应的值 
	}
	
	//递归求值 
	if (now->opt == '+') return GetVal(now->left) + GetVal(now->right);
	else if (now->opt == '-') return GetVal(now->left) - GetVal(now->right);
	else if (now->opt == '*') return GetVal(now->left) * GetVal(now->right);
	else if (now->opt == '/') return GetVal(now->left) / GetVal(now->right);
	else if (now->opt == '^') return (int)pow(GetVal(now->left), GetVal(now->right));
	else return 0; //异常处理 
}

//构建合并表达式 
void ExprTree::CompoundExpr(char opt, ExprTree e1, ExprTree e2)
{
	root = new Node();
	root->flag = 1, root->opt = opt;
	root->left = e1.GetRoot(), root->right = e2.GetRoot();
	this->s.assign(1, opt);
	this->s += e1.GetExpr() + e2.GetExpr();
}

//返回根节点 
Node* ExprTree::GetRoot()
{
	return root;
}

//返回前缀表达式 
string ExprTree::GetExpr()
{
	return s;
}

//合并常数项入口函数 
void ExprTree::MergeConstIntro()
{
	if (root->flag != 1) return;
	MergeConst(root); //合并常数项 
	s = "";
	UpdateExpr(root); //更新前缀表达式 
} 

//合并常数项 
void ExprTree::MergeConst(Node *now)
{
	if (now->left != nullptr) {
		if (now->left->flag == 2 && now->right->flag == 2) {
			now->flag = 2;
			if (now->opt == '+') {
				now->num = now->left->num + now->right->num;
			}
			else if (now->opt == '-') {
				now->num = now->left->num - now->right->num;
			}
			else if (now->opt == '*') {
				now->num = now->left->num * now->right->num;
			}
			else if (now->opt == '/') {
				now->num = now->left->num / now->right->num;
			}
			else if (now->opt == '^') {
				now->num = (int)pow(now->left->num, now->right->num);
			}
			now->left = nullptr, now->right = nullptr;
		}
		return;
	}
	
	MergeConst(now->left);
	MergeConst(now->right);
}

//更新前缀表达式 
void ExprTree::UpdateExpr(Node *now)
{
	if (now == nullptr) return;
	
	if (now->flag == 1) s += now->opt;
	else if (now->flag == 2) s += " "+to_string(now->num);
	else s += now->var;
	
	UpdateExpr(now->left);
	UpdateExpr(now->right);
}
#endif
