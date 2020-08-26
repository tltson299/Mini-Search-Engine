#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <time.h>
#include <algorithm>
#include <filesystem>
#include <sstream>
#include <cwchar>
#include <windows.h>
using namespace std;
using namespace std::filesystem;

// NODE
class Node
{
public:
	bool isLeaf;
	vector<int> myv;
	map<char, Node*> mapkey;
};

// TREE
class Trie
{
public:
	Node* root = nullptr;
	Node* createNode();
	void insert(Node*& root, char* str, int i);
	Node* getFile(Node* root, char* str);
	void deleteTrie(Node*& root);
};
// OTHER FUNCTIONS
void lowerChar(char*& str);
void lowerString(string& str);
bool isDuplicate(vector<int> a, int b);
vector<int> mergeVector(vector<int> a, vector<int> b);

#endif  // !_FUNCTION_H_