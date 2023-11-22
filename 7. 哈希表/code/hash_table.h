#ifndef _Hash_table
#define _Hash_table

#include <vector>
#include <random>
#include <utility>
#include <iostream>
#include <iomanip>
#define MAXSIZE 19 //table size is twice larger than record size, plus ensuring table size is a prime plus 
using namespace std;

//pseudo random sequence 
const int Seq[7] = {0, rand()%MAXSIZE, rand()%MAXSIZE, rand()%MAXSIZE, rand()%MAXSIZE, rand()%MAXSIZE, rand()%MAXSIZE};

class HashTable {
public:
	HashTable() {
		m_hash_table.clear();
		m_hash_table.resize(MAXSIZE);
	}
	~HashTable() {}
	
	int hash_func(string);			//hash function
	int find_addr1(string);			//obtain final hash address, using pseudo random sequence
	int find_addr2(string);			//obtain final hash address, using square detection method
	bool insert(string, int);		//insert an element, using two methods, the latter argument indicates the method type
	bool remove(string, int);		//delete an element, using two methods
	void print();					//print hash table 
private:
	//pair's first element(type int) indicates whether this position is empty(0), or filled(1), or deleted(2)
	//pair's second element(type string) indicates the value, in this case, value is same to key
	vector<pair<int, string>> m_hash_table;  
};

//hash function
int HashTable::hash_func(string name)
{
	int addr = 0;
	for (int i = 0; i <= name.size(); i++) {
		addr = (addr+name[i])%MAXSIZE; 
	}
	return addr;
}

//obtain final hash address, using pseudo random sequence
int HashTable::find_addr1(string name)
{
	int addr = hash_func(name);
	
	for (int i = 0; i < 7; i++) {
		addr = (addr+Seq[i]) % MAXSIZE;
		//find it
		if (m_hash_table[addr].first == 0 || m_hash_table[addr].first == 1 && m_hash_table[addr].second == name) {
			return addr;
		}
	}
	return -1; //not found
}

//obtain final hash address, using square detection method
int HashTable::find_addr2(string name)
{
	int addr = hash_func(name);
	
	//first find succeeds
	if (m_hash_table[addr].first == 0 || m_hash_table[addr].first == 1 && m_hash_table[addr].second == name) {
		return addr;
	}
	
	for (int i = 0; i < 7; i++) {
		addr = (addr+2*i+1) % MAXSIZE;
		//find it
		if (m_hash_table[addr].first == 0 || m_hash_table[addr].first == 1 && m_hash_table[addr].second == name) {
			return addr;
		}
	}
	return -1; //not found
}

//insert an element, using two methods, the latter argument indicates the method type
bool HashTable::insert(string name, int type)
{
	int addr;
	
	if (type == 1) addr = find_addr1(name);
	else addr = find_addr2(name);
	
	if (addr == -1) return false; //maybe no space
	
	m_hash_table[addr].first = 1; //flag as filled
	m_hash_table[addr].second = name;
	return true;
}

//delete an element, using two methods
bool HashTable::remove(string name, int type)
{
	int addr;
	
	if (type == 1) addr = find_addr2(name);
	else addr = find_addr2(name);
	 
	if (addr == -1 || m_hash_table[addr].first == 0) return false; //maybe no that name
	
	m_hash_table[addr].first = 2; //flag as deleted
	return true;
}

//print hash table
void HashTable::print()
{
	cout << "hash table size: " << MAXSIZE << '\n'; 

	//because of the limit of console size, I have to print twice
	
	cout << right << setfill('-') << setw(15*(MAXSIZE/2+1)+2) << '\n' << setfill(' ') << left;
	//print position
	cout << setw(4) << "|" << setw(11) << "position";
	for (int i = 0; i < MAXSIZE/2; i++) {
		cout << setw(7) << "|" << setw(8) << i;
	}
	cout << "|\n";
	//print name
	cout << setw(6) << "|" << setw(9) << "name";
	for (int i = 0; i < MAXSIZE/2; i++) {
		if (m_hash_table[i].first == 1) {
			int len = m_hash_table[i].second.size();
			cout << setw((15-len)/2+1) << "|" << setw(14-(15-len)/2) << m_hash_table[i].second;
		}
		else cout << setw(15) << "|";
	}
	cout << "|\n";
	
	cout << right << setfill('-') << setw(15*(MAXSIZE-MAXSIZE/2+1)+2) << '\n' << setfill(' ') << left;
	//print position
	cout << setw(4) << "|" << setw(11) << "position";
	for (int i = MAXSIZE/2; i < MAXSIZE; i++) {
		cout << setw(7) << "|" << setw(8) << i;
	}
	cout << "|\n";
	//print name
	cout << setw(6) << "|" << setw(9) << "name";
	for (int i = MAXSIZE/2; i < MAXSIZE; i++) {
		if (m_hash_table[i].first == 1) {
			int len = m_hash_table[i].second.size();
			cout << setw((15-len)/2+1) << "|" << setw(14-(15-len)/2) << m_hash_table[i].second;
		}
		else cout << setw(15) << "|";
	}
	cout << "|\n";
}

#endif
