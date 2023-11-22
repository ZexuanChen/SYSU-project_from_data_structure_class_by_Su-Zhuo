#include "textAnaTool.h"

//构造函数 
TextAnaTool::TextAnaTool()
{
	clear();
}

//析构函数 
TextAnaTool::~TextAnaTool() 
{
	fin.clear();
}

//清空成员变量 
void TextAnaTool::clear()
{
	n = count = 0;
	memset(trie, 0, sizeof trie);
	memset(fail, 0, sizeof fail);
	memset(toWord, 0, sizeof toWord);
}

//创建文件输入流
bool TextAnaTool::buildStream(string & textName)
{
	fin.open(textName);
	if (!fin.is_open()) {
		return false;
	}
	return true;
}

//读取待匹配字符串 
void TextAnaTool::readWords()
{
	cout << "请输入待统计词汇的个数：";
	cin >> n;
	words.resize(n+1); //让下标从1开始 
	cout << "请输入待统计词汇集：";
	for (int i = 1; i <= n; i++) {
		cin >> words[i].str;
		words[i].cnt = words[i].sgcnt = words[i].firstRow = 0;
	}
}

//构建字典树 
void TextAnaTool::createTrie()
{
	for (int i = 1; i <= n; i++) {
		string s = words[i].str;
		
		int root = 0;
		//往字典树插入单个字符串 
	    for (size_t j = 0; j < s.size(); j++) {
	        int next = s[j];
	        if (!trie[root][next]) trie[root][next] = ++count;
	        root = trie[root][next];
	    }
	    toWord[root] = i; //节点对应到字符串，之后匹配的时候判断依据是节点 
	}
}

//计算失配指针 
void TextAnaTool::getFail()
{
	queue<int> q;
    for (int i = 0; i < 128; i++) { //将第二层所有出现了的字母扔进队列 
        if (trie[0][i]) {
            q.push(trie[0][i]);
        }
    }
    
    while (!q.empty()) {
        int now = q.front();
        q.pop();

        for (int i = 0; i < 128; i++) { //查询ASCII码
            if (trie[now][i]) {
            	/*子节点的失配指针指向父节点失配指针所指节点的相应子节点*/
				/*子节点的失配指针指向的节点和该节点的字符是一样的，可以理解为一个最大后缀子串*/ 
				fail[trie[now][i]] = trie[fail[now]][i];  
            	q.push(trie[now][i]);
            }
			else {
				/*否则就让当前节点的这个子节点指向当前节点fail指针的对应子节点*/ 
				trie[now][i] = trie[fail[now]][i];
			}
		}	
    }
}

//打印每一行计数结果
void TextAnaTool::printLineRes(int row)
{
	cout << setfill('-') << setw(100) << "" << '\n' << setfill(' ');
	cout << "第" << row << "行计数的结果为：\n";
	
	for (int i = 1; i <= n; i++) {
		cout << setw(10) << words[i].str;
	}
	cout << endl;
	
	for (int i = 1; i <= n; i++) {
		cout << setw(10) << words[i].sgcnt;
	}
	cout << endl;
}

//打印最终排序统计结果 
void TextAnaTool::printLastRes()
{
	sort(words.begin()+1, words.end()); //按词频降序
	//表头
	cout << setfill('-') << setw(100) << "" << '\n' << setfill(' ');
	cout << "最终统计结果如下：\n";
	cout << setw(5) << "序号" << setw(15) << "匹配词汇" << setw(10) << "出现次数" << "首次出现行号\n";
	
	//内容 
	for (int i = 1; i <= n; i++) {
		cout << setw(5) << i << setw(15) << words[i].str << setw(10) << words[i].cnt;
		if (words[i].firstRow == 0) cout << "未出现\n";
		else cout << words[i].firstRow << '\n'; 
	}
	cout << endl;
}

//主要分析过程
void TextAnaTool::analyse()
{
	createTrie();
	getFail();
	
	string s;
	int row = 1; //行号
	//一行一行统计，空行结束 
    while (getline(fin, s)) {
    	//清空行的计数 
		for (int i = 1; i <= n; i++) {
			words[i].sgcnt = 0;
		}
		
    	int now = 0; 
    	for (size_t i = 0; i < s.size(); i++) {
	        now = trie[now][s[i]]; //从s[i]点开始寻找
	        
	        //一直用失配指针匹配以now结尾的所有模式串
	        for (int j = now; j; j = fail[j]) {
	            //如果当前节点对应了一个字符串，那么匹配成功 
	            if (toWord[j]) {
	            	words[toWord[j]].sgcnt++, words[toWord[j]].cnt++; //统计次数 
					if (words[toWord[j]].firstRow == 0) words[toWord[j]].firstRow = row; //统计行号 
				} 
	        }
	    }
	    
		printLineRes(row); //打印该行统计结果
		row++;
	}
	printLastRes(); //打印最后结果 
	
	//关闭流，清空流状态 
	fin.close();
	fin.clear();
}
