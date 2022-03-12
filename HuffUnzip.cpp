#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Node{
    public:
    int key;
    unsigned char s;
    Node *left;
    Node *right;
    
    Node(){
        key = 0;
        s = 0;
        left = nullptr;
		right = nullptr;
    }
	
	Node(unsigned char _s, int k){
	    s = _s;
		key = k;
		left = nullptr;
		right = nullptr;
	}

    Node(Node *l, Node *r){
        left =  l;
        right = r;
        key = l->key + r->key;
    }
};

void TreeGo(Node* Head, vector<bool>code, map<char, vector<bool>> *buff){
    if (Head->left){
	    code.push_back(0);
        TreeGo(Head->left, code, buff);
    }
    if (Head->right){
        code.push_back(1);
        TreeGo(Head->right, code, buff);
	}
	if (((Head->right) == NULL) && ((Head->left) == NULL))
        (*buff)[Head->s] = code;
    if (!code.empty()) 
		code.pop_back();
}

