#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <list>
#include <map>

using namespace std;

class Uzel{
	public:
	char s;  //символ
	int key; //частота
	Uzel *left, *right;
	Uzel(){
		left = NULL;
		right = NULL;
	};
	Uzel (char s, int k){
		this.s = s;
		this.key = k;
		left = NULL;
		right = NULL;
	};
	Uzel (Uzel *l; Uzel *r){
		this.key = l -> + r -> l;
		this.left = l;
		this.right = r;
	};
}

int main (){
	list <Uzel> List;
	map  <char, int> mp;
	ifstream file("input.txt");
	if (file.is_open()) {
		int a, b, size;
		file >> size;
		BoolM BM(size, size);
		do {
			file >> a;
			file >> b;
			BM.bm[a - 1].Set1(b - 1);
		} while (!file.eof());
		file.close();
		*this = BM;
		return size;
	};
}
