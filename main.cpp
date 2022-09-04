/*
Author: Suleman Rehman
*/
#include<iostream>
#include<string>
#include<queue>
#include<unordered_map>
#include<fstream>

using namespace std;


struct Node {
	int freq;
	char ch;
	Node* left;
	Node* right;
};
int encodedStringLength;
struct compare {
	//comparing frequencies of two nodes and returning bool
	bool operator() (Node* l, Node* r)
	{
		return l->freq > r->freq;
	}
};

Node* createNode(char c, int f, Node* l, Node* r)
{
	Node* t = new Node();

	t->ch = c;
	t->freq = f;
	t->left = l;
	t->right = r;

	return t;
}
void Encode(Node* root, string str, unordered_map<char, string>& hCode)
{
	if (root == nullptr)
		return;
	if (!root->left && !root->right) {
		hCode[root->ch] = str;
	}
	Encode(root->right, str + "1", hCode);
	Encode(root->left, str + "0", hCode);
}
void HuffmanTree(string s)
{
	unordered_map<char, int>freq;
	for (char c : s) {
		freq[c]++;
	} // Count frequency of each character and store it in map

	priority_queue<Node*, vector<Node*>, compare> pqueue;

	for (auto p : freq)
	{
		pqueue.push(createNode(p.first, p.second, nullptr, nullptr));
	}
	while (pqueue.size() > 1)
	{
		Node* left = pqueue.top();
		pqueue.pop();
		Node* right = pqueue.top();
		pqueue.pop();
		int s = left->freq + right->freq;
		pqueue.push(createNode('\0', s, left, right));
	}

	Node* root = pqueue.top();

	unordered_map<char, string>hCode;
	Encode(root, "", hCode);
	cout << "Printing the huffman codes: \n" << endl;
	for (auto p : hCode)
	{
		cout << p.first << " " << p.second << endl;
	}

	//printing encoded string

	string str = "";
	for (char c : s) {
		str += hCode[c];
	}
	cout << "\n\nEncoded string: " << endl;
	cout << str << endl;
	encodedStringLength = str.size();
}
int main()
{
	string str;
	ifstream file("huffman.txt");
	getline(file, str, '\n');
	file.close();
	cout << "Original String: "<< str << endl <<endl;
	HuffmanTree(str);
	int originalLength = str.size()*8;
	float compressionRatio = originalLength / encodedStringLength;
	cout << endl << "Compression Ratio: " << 100/compressionRatio << "%" << endl;
	return 0;

}

