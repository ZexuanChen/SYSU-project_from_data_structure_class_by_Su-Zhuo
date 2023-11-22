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
	TextAnaTool();      //Ĭ�Ϲ��캯��
	~TextAnaTool();     //�������� 
	void clear();       //��ճ�Ա���� 
	bool buildStream(string &);  //�����ļ��� 
	void readWords();       //����ͳ�ƴʻ㼯
	void createTrie();      //�����ֵ��� 
	void getFail();         //����֧��ָ�� 
	void printLineRes(int row); //��ӡÿһ�м������
	void printLastRes();    //��ӡ���ս�� 
	void analyse();         //�ı����� 
private:
	struct Word {        //�����ʻ����Ϣ 
		string str;      //�ʻ����� 
		int cnt, sgcnt;  //�ôʻ�����ܴ�����ÿ�г��ֵĴ��� 
		int firstRow;    //�ôʻ��һ�γ��ֵ��к�
		Word() {         //Ĭ�Ϲ��캯�� 
			str = "";
			cnt = firstRow = sgcnt = 0;
		}
		
		bool operator < (const Word & b) const { //�������� 
			return cnt >= b.cnt;
		}
	};
	
	ifstream fin;            //�ļ������� 
	int n;                   //�ʻ���� 
	vector<Word> words;      //�ʻ㼯 
	
	int trie[N][128], count;  //�ֵ�������ڵ��� 
	int fail[N], toWord[N];  //�ֵ����ڵ��ʧ��ָ��Ͷ�Ӧ�Ĵʻ��ţ�������Ӧ�ʻ��ţ���Ϊ0 
};

#endif 
