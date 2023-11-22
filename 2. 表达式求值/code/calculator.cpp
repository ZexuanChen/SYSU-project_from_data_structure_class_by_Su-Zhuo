#include "calculator.h"

Calculator::Calculator()
{
	clear();
	cout << left; //设置输出左对齐，方便后面展示运算过程
}

Calculator::~Calculator() {}

void Calculator::clear() 
{
	while (!opt_stack.empty()) opt_stack.pop();
	while (!num_stack.empty()) num_stack.pop();
	expression = "";
	res = cnt = 0;
} 

//获得表达式 
void Calculator::getS(string s)
{
	expression = s;
}

//返回结果
int Calculator::getRes()
{
	return res;
}

//求值 
void Calculator::eval()
{
	cout << "求值过程如下：\n";
	cout << setfill('-') << setw(100) << "" << '\n'; 
	cout << setfill(' ') << setw(6) << "步骤" << setw(25) << "运算符栈" << setw(25) << "运算数栈" 
	     << setw(25) << "输入字符" << "操作\n"; //显示内容的头部 
	
	int len = expression.size(), pos = 0;
	
	//遍历字符串 
	while (pos < len) {
		char ch = expression[pos]; //当前操作字符
		string opt(1, ch); //转换成字符串，方便后续打印过程 
		//如果为空格 
		if (ch == ' ') {
			pos++;
		}
		//如果为除'('、')'外运算符
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
			while (!opt_stack.empty() && m[ch] <= m[opt_stack.top()]) { //弹出所有优先级>=ch的运算符 
				process(opt_stack.top()); //运算符栈弹出一个元素后的单步处理 
				string opt(1, opt_stack.top());
				opt_stack.pop();
				show(1, opt, pos); //打印该步信息 
			}
			opt_stack.push(ch);
			pos++;
			show(2, opt, pos); //打印该步信息 
		}
		//如果为'('运算符
		else if (ch == '(') {
			//直接压入，不做其它操作
			opt_stack.push(ch);
			pos++;
			show(2, opt, pos);
		}
		//如果为')'运算符 
		else if (ch == ')') {
			while (opt_stack.top() != '(') { //不断弹出运算符，直到遇到左括号 
				process(opt_stack.top());
				string opt(1, opt_stack.top());
				opt_stack.pop();
				show(1, opt, pos);
			}
			opt_stack.pop(); //弹出'('
			pos++;
			show(1, opt, pos); //相当于弹出')'
		}
		//如果为操作数 
		else {
			int num = 0;
			//将字符序列转换为整数
            while (pos < expression.size() && expression[pos] >= '0' && expression[pos] <= '9') {
                num = num*10 + expression[pos] - '0';
                pos++;
            }
            num_stack.push(num);
            opt = to_string(num);
            show(2, opt, pos);
		}
	}
	
	//将运算符栈剩余元素弹出 
	while (!opt_stack.empty()) {
		process(opt_stack.top());
		string opt(1, opt_stack.top());
		opt_stack.pop();
		show(1, opt, pos);
	}
	res = num_stack.top();
	
	cout << "操作结束！！运算数栈剩余的即是答案~\n";
}

//运算符弹出后的单步操作 
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

//将栈的内容转换成字符串, 1表示转换运算符栈，2表示转换运算数栈
string Calculator::stackToStr(int flag) {
	string s;
	if (flag == 1) {//转换运算符栈 
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
	else { //转换运算数栈 
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

//打印过程, opt为操作数，可能是运算符，也可能是运算数 
void Calculator::show(int witch, string opt, int pos)
{
	string opt_str; //操作内容
	//如果是弹栈操作 
	if (witch == 1) {
		opt_str = "弹出" + opt;
		if (opt != ")") opt_str += ", 弹出运算数栈两个元素, 进行相应运算后再压入"; 
	}
	//如果是压栈操作 
	else {
		opt_str = "压入" + opt; 
	} 

	cout << setw(6) << ++cnt << setw(25) << stackToStr(1) << setw(25) << stackToStr(2) 
	     << setw(25) << expression.substr(pos) + "#" << opt_str << '\n';
}
