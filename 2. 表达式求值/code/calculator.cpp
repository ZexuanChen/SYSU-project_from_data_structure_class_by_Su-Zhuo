#include "calculator.h"

Calculator::Calculator()
{
	clear();
	cout << left; //�����������룬�������չʾ�������
}

Calculator::~Calculator() {}

void Calculator::clear() 
{
	while (!opt_stack.empty()) opt_stack.pop();
	while (!num_stack.empty()) num_stack.pop();
	expression = "";
	res = cnt = 0;
} 

//��ñ��ʽ 
void Calculator::getS(string s)
{
	expression = s;
}

//���ؽ��
int Calculator::getRes()
{
	return res;
}

//��ֵ 
void Calculator::eval()
{
	cout << "��ֵ�������£�\n";
	cout << setfill('-') << setw(100) << "" << '\n'; 
	cout << setfill(' ') << setw(6) << "����" << setw(25) << "�����ջ" << setw(25) << "������ջ" 
	     << setw(25) << "�����ַ�" << "����\n"; //��ʾ���ݵ�ͷ�� 
	
	int len = expression.size(), pos = 0;
	
	//�����ַ��� 
	while (pos < len) {
		char ch = expression[pos]; //��ǰ�����ַ�
		string opt(1, ch); //ת�����ַ��������������ӡ���� 
		//���Ϊ�ո� 
		if (ch == ' ') {
			pos++;
		}
		//���Ϊ��'('��')'�������
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
			while (!opt_stack.empty() && m[ch] <= m[opt_stack.top()]) { //�����������ȼ�>=ch������� 
				process(opt_stack.top()); //�����ջ����һ��Ԫ�غ�ĵ������� 
				string opt(1, opt_stack.top());
				opt_stack.pop();
				show(1, opt, pos); //��ӡ�ò���Ϣ 
			}
			opt_stack.push(ch);
			pos++;
			show(2, opt, pos); //��ӡ�ò���Ϣ 
		}
		//���Ϊ'('�����
		else if (ch == '(') {
			//ֱ��ѹ�룬������������
			opt_stack.push(ch);
			pos++;
			show(2, opt, pos);
		}
		//���Ϊ')'����� 
		else if (ch == ')') {
			while (opt_stack.top() != '(') { //���ϵ����������ֱ������������ 
				process(opt_stack.top());
				string opt(1, opt_stack.top());
				opt_stack.pop();
				show(1, opt, pos);
			}
			opt_stack.pop(); //����'('
			pos++;
			show(1, opt, pos); //�൱�ڵ���')'
		}
		//���Ϊ������ 
		else {
			int num = 0;
			//���ַ�����ת��Ϊ����
            while (pos < expression.size() && expression[pos] >= '0' && expression[pos] <= '9') {
                num = num*10 + expression[pos] - '0';
                pos++;
            }
            num_stack.push(num);
            opt = to_string(num);
            show(2, opt, pos);
		}
	}
	
	//�������ջʣ��Ԫ�ص��� 
	while (!opt_stack.empty()) {
		process(opt_stack.top());
		string opt(1, opt_stack.top());
		opt_stack.pop();
		show(1, opt, pos);
	}
	res = num_stack.top();
	
	cout << "������������������ջʣ��ļ��Ǵ�~\n";
}

//�����������ĵ������� 
void Calculator::process(char ch)
{
	int b = num_stack.top();
	num_stack.pop();
	int a = num_stack.top();
	num_stack.pop();
	
	switch (ch) {
		case '-':
			num_stack.push(a-b);
			break;
		case '+':
			num_stack.push(a+b);
			break;
		case '*':
			num_stack.push(a*b);
			break;
		case '/':
			num_stack.push(a/b);
			break;
		case '^':
			num_stack.push((int)pow(a, b));
			break;
		default:
			break;
	}
}

//��ջ������ת�����ַ���, 1��ʾת�������ջ��2��ʾת��������ջ
string Calculator::stackToStr(int flag) {
	string s;
	if (flag == 1) {//ת�������ջ 
		stack<char> tmp(opt_stack);
		vector<char> v;
		while (!tmp.empty()) {
			v.push_back(tmp.top());
			tmp.pop();
		}
		for (int i = v.size()-1; i >= 0; i--) {
			s.push_back(v[i]);
		}
	}
	else { //ת��������ջ 
		stack<int> tmp(num_stack);
		vector<int> v;
		while (!tmp.empty()) {
			v.push_back(tmp.top());
			tmp.pop();
		} 
		for (int i = v.size()-1; i >= 0; i--) {
			s += to_string(v[i]) + " ";
		}
	}
	return s;
}

//��ӡ����, optΪ���������������������Ҳ������������ 
void Calculator::show(int witch, string opt, int pos)
{
	string opt_str; //��������
	//����ǵ�ջ���� 
	if (witch == 1) {
		opt_str = "����" + opt;
		if (opt != ")") opt_str += ", ����������ջ����Ԫ��, ������Ӧ�������ѹ��"; 
	}
	//�����ѹջ���� 
	else {
		opt_str = "ѹ��" + opt; 
	} 

	cout << setw(6) << ++cnt << setw(25) << stackToStr(1) << setw(25) << stackToStr(2) 
	     << setw(25) << expression.substr(pos) + "#" << opt_str << '\n';
}
