#include "function.h"
Node* Trie::createNode()
{
	Node* node = new Node;
	node->isLeaf = false;
	return node;
}
void Trie::insert(Node*& root, char* str, int i)
{
	if (root == NULL)
		root = createNode();
	lowerChar(str);
	Node* cur = root;
	while (*str)
	{
		lowerChar(str);
		if (cur->mapkey.find(*str) == cur->mapkey.end())
			cur->mapkey[*str] = createNode();
		cur = cur->mapkey[*str];
		str++;
	}
	//if(!cur->myv.empty()) cout << cur->myv.back()<<" ";
	if (cur->myv.empty())
		cur->myv.push_back(i);
	if ((!cur->myv.empty()) && i > cur->myv.back())
		cur->myv.push_back(i);
	cur->isLeaf = true;
}
void Trie::deleteTrie(Node*& root)
{
	map<char, Node*>::iterator it;
	if (root == NULL)
		return;
	for (it = root->mapkey.begin(); it != root->mapkey.end(); it++)
		deleteTrie(it->second);
	delete root;
}
// similar to search function but this function also get the leaf node
Node* Trie::getFile(Node* root, char* str)
{
	lowerChar(str);
	if (root == NULL)
		return NULL;
	Node* cur = root;
	while (*str)
	{
		cur = cur->mapkey[*str];
		if (cur == NULL)
			return NULL;
		str++;
	}
	return cur;
}
void lowerChar(char*& str)
{
	int n = strlen(str);
	for (int i = 0; i < n; ++i)
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += ('a' - 'A');
}
void lowerString(string& str)
{
	int n = str.length();
	for (int i = 0; i < n; ++i)
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += ('a' - 'A');
}
// merge 2 vector
bool isDuplicate(vector<int> a, int b)
{
	for (int i = 0; i < a.size(); ++i)
		if (b == a.at(i))
			return true;
	return false;
}
vector<int> mergeVector(vector<int> a, vector<int> b)
{
	for (int i = 0; i < b.size(); ++i)
	{
		if (!isDuplicate(a, b.at(i)))
			a.push_back(b.at(i));
	}
	return a;
}
