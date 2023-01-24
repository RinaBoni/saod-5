#include <iostream>
#include <fstream>
#include <time.h>
#include "TreeNode.h"
using namespace std;

int main()
{
    //подключаем файл для вывода
    string s = "rezult.txt";
    //открываем файл для записи
	ofstream file(s, ios_base::app);
	//для рандомных чисел
    srand(time(0));
	//количество элементов очереди или узлов дерева
	queue<int> D1;
	setlocale(0, "");
	
    D1.push(50);
    D1.push(60);
    D1.push(40);
    D1.push(45);
    D1.push(65);

    D1.push(55);
    D1.push(35);
    D1.push(62);
    D1.push(58);
    D1.push(68);

    D1.push(20);
    D1.push(39);
    D1.push(36);
    D1.push(34);
    D1.push(67);

    //создаем узел дерева - корень
    TreeNode<int> *B1, * B2;
    //заполняем дерево очередью
    B1 = CreateBinTree(D1);

    //Горизонтальная печать дерева
    cout << "- - - - - -horizontally- - - - - -" << endl;
    file << "- - - - - -horizontally- - - - - -" << endl;
    PrintTree(B1, 0);
    PrintTreeFile(B1, 0, s);

    //копирование дерева
    B2 = CopyTree(B1);

    //вертикальная печать
    cout << "- - - - - -vertically- - - - - -" << endl;
    file << "- - - - - -vertically- - - - - -" << endl;

    PrintVTreeFile(B2, 0, 64, PrintFile, s);
    PrintVTree(B1, 0, 64, Print);

    file << endl;

    return 0;
}
