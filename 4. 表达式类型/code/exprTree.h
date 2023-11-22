#ifndef ExprTree_H
#define ExprTree_H

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int cg[26]; //������Ӧ��ֵ����ʼֵΪ0

//�������ڵ㶨��
struct Node {
	int flag; //flag = 1��ʾ�������flag = 2��ʾ������flag = 3��ʾ����
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
	ExprTree() { //���캯����ֱ�Ӷ��� 
		root = nullptr;
		pos = 0;
		flag = false; 
	}
	~ExprTree() {} //�������� 
	
	bool ReadExpr(); //��ȡǰ׺���ʽ
	Node* toTree(); //���ʽת������ 
	void WriteExpr(Node*); //��׺������ʽ���ʵ�������
	int GetVal(Node*); //��ֵ
	void CompoundExpr(char opt, ExprTree E1, ExprTree E2); //�ϲ��������ʽ�γ�һ���µı��ʽ
	void MergeConstIntro(); //�ϲ���������ں���
	void MergeConst(Node*); //�ϲ������� 
	void UpdateExpr(Node*); //����ǰ׺���ʽ 
	Node* GetRoot(); //���ظ��ڵ� 
	string GetExpr(); //���ر��ʽ 
	
private:
	Node *root; //���ʽ���ĸ��ڵ� 
	string s; //ǰ׺���ʽ
	int pos; //���ʽת������λ��ָ�� 
	bool flag; //����Ϸ����ж� 
};

//����ǰ׺���ʽ 
bool ExprTree::ReadExpr() 
{
	cout << "��������ʽ��";
	getline(cin, s);
	
	flag = false;
	pos = 0;
	root = toTree();
	//ǰ׺���ʽ�Ϸ��Լ�� 
	for (; pos < s.size(); pos++) {
		if (s[pos] != ' ') {
			flag = true;
			break;
		}
	}
	
	if (flag) return false; //���ʽ���Ϸ�
	return true; 
}

//ǰ׺���ʽת��Ϊ���ʽ�� 
Node* ExprTree::toTree()
{
	if (flag) return nullptr;

	//���Կո� 
	if (s[pos] == ' ') {
		pos++; 
		return toTree(); //�����
	}
	//���Ϊ���ͳ��� 
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
	//���Ϊ���� 
	else if (s[pos] <= 'z' && s[pos] >= 'a') {
		Node* leap = new Node();
		leap->flag = 3, leap->var = s[pos];
		pos++;
		return leap;
	}
	//���Ϊ������
	else if (s[pos] == '+' || s[pos] == '-' || s[pos] == '*' || s[pos] == '/' || s[pos] == '^') {
		Node *now = new Node(); //�����ڵ� 
		now->flag = 1, now->opt = s[pos];
		pos++;
		if (pos >= s.size()) { //�Ϸ��Լ�� 
			flag = true;
			return nullptr;
		}
		now->left = toTree(); //�ݹ������� 
		if (pos >= s.size()) { //�Ϸ��Լ�� 
			flag = true;
			return nullptr;
		}
		now->right = toTree(); //�ݹ�������
		return now; 
	} 
	else { //�Ϸ��Լ�� 
		flag = true;
		return nullptr;
	}
}

//��׺��ʽ������ʽ 
void ExprTree::WriteExpr(Node* now)
{
	//��������Ϊ�������� 
	if (now->flag == 2) {
		cout << now->num;
		return;
	}
	if (now->flag == 3) {
		cout << now->var;
		return;
	}
	
	//�ݹ���� 
	if (now != root) cout << '(';
	WriteExpr(now->left); //��ݹ� 
	
	cout << now->opt; //�������� 
	
	WriteExpr(now->right); //�ҵݹ�
	if (now != root) cout << ')';
	return;
}

//��ֵ
int ExprTree::GetVal(Node* now)
{
	//��������� 
	if (now->flag == 2) {
		return now->num;
	}
	if (now->flag == 3) {
		return cg[now->var-'a']; //����ת��Ϊ��Ӧ��ֵ 
	}
	
	//�ݹ���ֵ 
	if (now->opt == '+') return GetVal(now->left) + GetVal(now->right);
	else if (now->opt == '-') return GetVal(now->left) - GetVal(now->right);
	else if (now->opt == '*') return GetVal(now->left) * GetVal(now->right);
	else if (now->opt == '/') return GetVal(now->left) / GetVal(now->right);
	else if (now->opt == '^') return (int)pow(GetVal(now->left), GetVal(now->right));
	else return 0; //�쳣���� 
}

//�����ϲ����ʽ 
void ExprTree::CompoundExpr(char opt, ExprTree e1, ExprTree e2)
{
	root = new Node();
	root->flag = 1, root->opt = opt;
	root->left = e1.GetRoot(), root->right = e2.GetRoot();
	this->s.assign(1, opt);
	this->s += e1.GetExpr() + e2.GetExpr();
}

//���ظ��ڵ� 
Node* ExprTree::GetRoot()
{
	return root;
}

//����ǰ׺���ʽ 
string ExprTree::GetExpr()
{
	return s;
}

//�ϲ���������ں��� 
void ExprTree::MergeConstIntro()
{
	if (root->flag != 1) return;
	MergeConst(root); //�ϲ������� 
	s = "";
	UpdateExpr(root); //����ǰ׺���ʽ 
} 

//�ϲ������� 
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

//����ǰ׺���ʽ 
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
