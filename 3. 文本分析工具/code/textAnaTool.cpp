#include "textAnaTool.h"

//���캯�� 
TextAnaTool::TextAnaTool()
{
	clear();
}

//�������� 
TextAnaTool::~TextAnaTool() 
{
	fin.clear();
}

//��ճ�Ա���� 
void TextAnaTool::clear()
{
	n = count = 0;
	memset(trie, 0, sizeof trie);
	memset(fail, 0, sizeof fail);
	memset(toWord, 0, sizeof toWord);
}

//�����ļ�������
bool TextAnaTool::buildStream(string & textName)
{
	fin.open(textName);
	if (!fin.is_open()) {
		return false;
	}
	return true;
}

//��ȡ��ƥ���ַ��� 
void TextAnaTool::readWords()
{
	cout << "�������ͳ�ƴʻ�ĸ�����";
	cin >> n;
	words.resize(n+1); //���±��1��ʼ 
	cout << "�������ͳ�ƴʻ㼯��";
	for (int i = 1; i <= n; i++) {
		cin >> words[i].str;
		words[i].cnt = words[i].sgcnt = words[i].firstRow = 0;
	}
}

//�����ֵ��� 
void TextAnaTool::createTrie()
{
	for (int i = 1; i <= n; i++) {
		string s = words[i].str;
		
		int root = 0;
		//���ֵ������뵥���ַ��� 
	    for (size_t j = 0; j < s.size(); j++) {
	        int next = s[j];
	        if (!trie[root][next]) trie[root][next] = ++count;
	        root = trie[root][next];
	    }
	    toWord[root] = i; //�ڵ��Ӧ���ַ�����֮��ƥ���ʱ���ж������ǽڵ� 
	}
}

//����ʧ��ָ�� 
void TextAnaTool::getFail()
{
	queue<int> q;
    for (int i = 0; i < 128; i++) { //���ڶ������г����˵���ĸ�ӽ����� 
        if (trie[0][i]) {
            q.push(trie[0][i]);
        }
    }
    
    while (!q.empty()) {
        int now = q.front();
        q.pop();

        for (int i = 0; i < 128; i++) { //��ѯASCII��
            if (trie[now][i]) {
            	/*�ӽڵ��ʧ��ָ��ָ�򸸽ڵ�ʧ��ָ����ָ�ڵ����Ӧ�ӽڵ�*/
				/*�ӽڵ��ʧ��ָ��ָ��Ľڵ�͸ýڵ���ַ���һ���ģ��������Ϊһ������׺�Ӵ�*/ 
				fail[trie[now][i]] = trie[fail[now]][i];  
            	q.push(trie[now][i]);
            }
			else {
				/*������õ�ǰ�ڵ������ӽڵ�ָ��ǰ�ڵ�failָ��Ķ�Ӧ�ӽڵ�*/ 
				trie[now][i] = trie[fail[now]][i];
			}
		}	
    }
}

//��ӡÿһ�м������
void TextAnaTool::printLineRes(int row)
{
	cout << setfill('-') << setw(100) << "" << '\n' << setfill(' ');
	cout << "��" << row << "�м����Ľ��Ϊ��\n";
	
	for (int i = 1; i <= n; i++) {
		cout << setw(10) << words[i].str;
	}
	cout << endl;
	
	for (int i = 1; i <= n; i++) {
		cout << setw(10) << words[i].sgcnt;
	}
	cout << endl;
}

//��ӡ��������ͳ�ƽ�� 
void TextAnaTool::printLastRes()
{
	sort(words.begin()+1, words.end()); //����Ƶ����
	//��ͷ
	cout << setfill('-') << setw(100) << "" << '\n' << setfill(' ');
	cout << "����ͳ�ƽ�����£�\n";
	cout << setw(5) << "���" << setw(15) << "ƥ��ʻ�" << setw(10) << "���ִ���" << "�״γ����к�\n";
	
	//���� 
	for (int i = 1; i <= n; i++) {
		cout << setw(5) << i << setw(15) << words[i].str << setw(10) << words[i].cnt;
		if (words[i].firstRow == 0) cout << "δ����\n";
		else cout << words[i].firstRow << '\n'; 
	}
	cout << endl;
}

//��Ҫ��������
void TextAnaTool::analyse()
{
	createTrie();
	getFail();
	
	string s;
	int row = 1; //�к�
	//һ��һ��ͳ�ƣ����н��� 
    while (getline(fin, s)) {
    	//����еļ��� 
		for (int i = 1; i <= n; i++) {
			words[i].sgcnt = 0;
		}
		
    	int now = 0; 
    	for (size_t i = 0; i < s.size(); i++) {
	        now = trie[now][s[i]]; //��s[i]�㿪ʼѰ��
	        
	        //һֱ��ʧ��ָ��ƥ����now��β������ģʽ��
	        for (int j = now; j; j = fail[j]) {
	            //�����ǰ�ڵ��Ӧ��һ���ַ�������ôƥ��ɹ� 
	            if (toWord[j]) {
	            	words[toWord[j]].sgcnt++, words[toWord[j]].cnt++; //ͳ�ƴ��� 
					if (words[toWord[j]].firstRow == 0) words[toWord[j]].firstRow = row; //ͳ���к� 
				} 
	        }
	    }
	    
		printLineRes(row); //��ӡ����ͳ�ƽ��
		row++;
	}
	printLastRes(); //��ӡ����� 
	
	//�ر����������״̬ 
	fin.close();
	fin.clear();
}
