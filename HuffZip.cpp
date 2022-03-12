#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <string>

using namespace std;

//Клас узел
class Node
{
    public:
    int key;           //Частота
    unsigned char s;   //Символ
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

//Леворекурсивный обход дерева и присваивание булева вектора каждому символу
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

int main(){
    //Оригинальный текст
    ifstream In("A.txt");
    if (!In.is_open()){ 
        cout << "error"; 
	return 0; 
    }
    //Сжатый файл
    ofstream Out("B.txt", ios::binary);
    if (!Out.is_open()){ 
        cout << "error"; 
        return 0; 
    }
	
    //Подсчет частоты появления каждого символа в тексте
    int Q[256]= {0};
    unsigned char s = 0;

    while((s = In.get()) && !In.eof())
	Q[s]++;
	
    //Указатель на начало файла
    In.clear();
    In.seekg(0, ios_base::beg);

    //Список узлов
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
	
    //Занимаем место в начале файла
    int n = 0;
    Out.write((char*)&n, sizeof(n));

    //Записываем количество пар (символ - частота)
    n = List.size();
    Out.write((char*)&n, sizeof(n));

    //Записываем пары (символ - частота)
    for (auto it: List){
        Out.write((char*)&it->s, sizeof(it->s));
        Out.write((char*)&it->key, sizeof(it->key));
    }
	
    //Строим дерево по списку
    while (List.size() != 1){
        Node *l = List.front();
        List.pop_front();
        Node *r = List.front();
        List.pop_front();

        Node *newUzel = new Node(l,r);

        auto iter = List.begin();

        for (; iter != List.end();){
            if (newUzel->key > (*iter)->key)
                iter++;
            else
                break;
        }
        List.insert(iter, newUzel);
    }
	
    //Присваиваем каждому символу булев вектор
    vector<bool> code;
    map<char, vector<bool>>* buff = new map<char, vector<bool>>;
    TreeGo(*(List.begin()), code, buff);

    //Формируем новые байты и записываем их в файл
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

    //Записываем последний байт
    if (!(count==0 && tx==0))
        Out.write((char*)&tx, 1);   

    //Настраиваемся на начало файла и записываем количество значимых бит в последнем байте
    Out.clear();
    Out.seekp(0);
    Out.write((char*)&count, sizeof(count));

    Out.close();
    In.close();    

    return 0;
}
    
