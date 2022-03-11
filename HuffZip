#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <string>

using namespace std;

class Node
{
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

int main(){
	ifstream In("A.txt");
	ofstream Out("B.txt", ios::binary);
	int Q[256]= {0};
	unsigned char s = 0;
	
	while((s = In.get()) && !In.eof())
		Q[s]++;
	
	In.clear();
    In.seekg(0, ios_base::beg);
	
	list<Node*> List;
	for (int i=0; i<256; i++){
		if (Q[i]==0)
			continue;
		Node* uzel = new Node(i, Q[i]);
		auto iter = List.begin();
		for (; iter != List.end();){
			if (uzel->key > (*iter)->key)
				iter++;
			else 
				break;
		}
		List.insert(iter, uzel);
	}
	
	int n = 0;
	Out.write((char*)&n, sizeof(n));
	
	n = List.size();
	Out.write((char*)&n, sizeof(n));
	
	for (auto it: List){
		Out.write((char*)&it->s, sizeof(it->s));
        Out.write((char*)&it->key, sizeof(it->key));
    }
	
	while (List.size() != 1){
		Node *l = List.front();
        List.pop_front();
        Node *r = List.front();
        List.pop_front();

        Node *newUzel = new Node(l,r);

        auto iter = List.begin();

        for (; iter != List.end();)
        {
            if (newUzel->key > (*iter)->key)
            {
                iter++;
                continue;
            }
            else
            {
                break;
            }
        }
        List.insert(iter, newUzel);
    }
	
	vector<bool> code;
    map<char, vector<bool>>* buff = new map<char, vector<bool>>;
    TreeGo(*(List.begin()), code, buff);

    unsigned char tx = 0;
    int count = 0;
    while ((s = In.get()) && !In.eof()){
        vector <bool> x = buff->at(s);
        for (size_t i = 0; i < x.size(); i++){
            tx = tx | x[i] << (7 - count);
            count++;
            if (count==8){
                count = 0;
                Out.write((char*)&tx, 1);
                tx = 0;
            }
        }
    }

    if (!(count==0 && tx==0))
        Out.write((char*)&tx, 1);   

    Out.clear();
    Out.seekp(0);
    Out.write((char*)&count, sizeof(count));
    Out.close();
    In.close();    

    return 0;
}
    
