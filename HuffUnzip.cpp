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
