#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Node{
    public:
    int key;            //Частота
    unsigned char s;    //Символ
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

//Леворекурсивный обход дерева 
void TreeGo(Node* Head, vector<bool>code, map<char, vector<bool>> *buff){
    if (Head->left){
	vector <bool> temp = code;
	temp.push_back(0);
        TreeGo(Head->left, temp, buff);
    }
    if (Head->right){
	vector <bool> temp = code;
        temp.push_back(1);
        TreeGo(Head->right, temp, buff);
    }
    if (Head->right) == nullptr && Head->left == nullptr)
        (*buff)[Head->s] = code;
    if (!code.empty()) 
	code.pop_back();
}

int main()
{
    //Сжатый файл
    ifstream In("B.txt", ios::binary);
    if (!In.is_open()){ 
        cout << "error"; 
        return 0; 
    }
	
    //Файл, куда записываем результат расжатия 
    ofstream Out("C.txt");
    if (!Out.is_open()){ 
        cout << "error"; 
        return 0; 
    }
	
    //Количество значимых бит в последнем байте
    int lastByte;
    In.read((char*)&lastByte, sizeof(lastByte));

    //Количество пар (символ - частота)
    int numberOfPairs;
    In.read((char*)&numberOfPairs, sizeof(numberOfPairs));
	
    //Чтение пар (символ - частота) и формирование списка узлов
    unsigned char s;
    int k;
    list<Node*>List;
    for (size_t i = 0; i < numberOfPairs; i++){
        In.read((char*)&s, sizeof(s));
        In.read((char*)&k, sizeof(k));

        Node* uzel = new Node(s, k);
        List.push_back(uzel);
    }
    

