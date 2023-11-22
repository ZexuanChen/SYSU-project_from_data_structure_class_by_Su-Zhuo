#ifndef _TextAnaTool_h
#define _TextAnaTool_h

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <cstring> 
using namespace std;

const int N = 1e3+5;

class TextAnaTool {
public:
	TextAnaTool();      //默认构造函数
	~TextAnaTool();     //析构函数 
	void clear();       //清空成员变量 
	bool buildStream(string &);  //创建文件流 
	void readWords();       //读待统计词汇集
	void createTrie();      //创建字典树 
	void getFail();         //计算支配指针 
	void printLineRes(int row); //打印每一行计数结果
	void printLastRes();    //打印最终结果 
	void analyse();         //文本分析 
private:
	struct Word {        //单个词汇的信息 
		string str;      //词汇内容 
		int cnt, sgcnt;  //该词汇出现总次数和每行出现的次数 
		int firstRow;    //该词汇第一次出现的行号
		Word() {         //默认构造函数 
			str = "";
			cnt = firstRow = sgcnt = 0;
		}
		
		bool operator < (const Word & b) const { //用于排序 
			return cnt >= b.cnt;
		}
	};
	
	ifstream fin;            //文件输入流 
	int n;                   //词汇个数 
	vector<Word> words;      //词汇集 
	
	int trie[N][128], count;  //字典树和其节点数 
	int fail[N], toWord[N];  //字典树节点的失配指针和对应的词汇编号，若不对应词汇编号，则为0 
};

#endif 
