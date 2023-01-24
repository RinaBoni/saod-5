#include <iostream>
#include "tree.cpp"

using namespace std;

int main() {
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	ThreeNode<int>* root, * levreb, * pravreb, * levreb_l, * pravreb_p; // объявление корня правого, левого
	ThreeNode<int>* p; // объявление текущего указателя
	pravreb_p = new ThreeNode<int>(7);
	levreb_l = new ThreeNode<int>(3);
	pravreb = new ThreeNode<int>(6, pravreb_p);
	levreb = new ThreeNode<int>(4, levreb_l);
	root = new ThreeNode<int>(5, levreb, pravreb);
	int n = 0;
	while (cin >> n)
		switch (n) {
		case 1:
			cout << "root -> levreb = " << levreb->data << endl;
			break;
		case 2:
			cout << "root -> pravreb = " << pravreb->data << endl;
			break;
		case 3:
			cout << "root -> levreb -> levreb_l = " << levreb_l->data << endl;
			break;
		case 4:
			cout << "root -> pravreb -> pravreb_p = " << pravreb_p->data << endl;
			break;
		case 0:
			cout << "root = " << root->data << endl;
			break;
		default:
			cout << "NO";
			break;
		}

	delete pravreb_p;
	delete levreb_l;
	delete levreb;
	delete pravreb;
	delete root;
}