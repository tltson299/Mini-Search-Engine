#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <time.h>
#include <algorithm>
#include <filesystem>
#include <sstream>
#include <cwchar>
#include <windows.h>
#include <thread>
using namespace std;
using namespace std::filesystem;

// NODE
class Node
{
public:
	bool isLeaf;
	vector<int> myv;
	unordered_map<char, Node*> mapkey;
};

// TREE
class Trie
{
public:
	Node* root = nullptr;
	~Trie()
	{
		deleteTrie(root);
	}
	Node* createNode();
	void insert(Node*& root, string str, int i);
	void readWord(vector<string>& ptr, Node*& root, int i);
	void readStop(string ptr, Node*& root, int i);
	void getFileName(Node*& root, char* str, vector<string>& vt);
	void removeStopWord(vector<string>& store, Node* root2);
	void deleteTrie(Node*& root);
	Node* getFile(Node* root, char* str);
	void QueryOperator(Node* root, char* str, vector<string>& vt, Node* root2);
	void commonVector(vector<int> inputvt, vector<int>& common);
	void ouputVector(vector<string> mys, string filename, bool& found, vector<string> highlight);
	bool checkString(string input, string word);
	bool checkOnVector(vector<string> input, string word);
	void ouputVectorEx(vector<string> mys, string filename, bool& found, vector<string> highlight, int pos);
	void outPutResult(string fileName, vector<string> input, int& count, bool exact, bool intitle);
	bool queryPrice(vector<string> input);
	bool queryHastag(vector<string> input);
	bool queryIntitle(string input);
	bool queryFileType(string input);
	bool queryExact(vector<string> input);
	bool queryRange(vector<string>& input, string& start, string& end, string& sim);
	void getQueryAnd(Node* root, vector<string>& store, char*& str2, vector<int>& common, int& countN, int qt);
	void getQueryOr(Node* root2, vector<string>& store, char*& str2, vector<int>& common, int& countN);
	bool queryMinus(vector<string>& input, vector<string>& minus);
	bool checkIntOnVector(vector<int>minus, int input);
	void checkPlus(vector<string>& input, Node* root2, vector<string>& result);
};

// OTHER FUNCTIONS
void title();
void lowerChar(char*& str);
void lowerString(string& str);
bool isDuplicate(vector<int> a, int b);
vector<int> mergeVector(vector<int> a, vector<int> b);
void fontSize(CONSOLE_FONT_INFOEX& cfi, int x, int y);

#endif // !_FUNCTION_H_