#include <iostream>
#include <fstream>
#include <time.h>
#include "AVLTree.h"
using namespace std;


//загрузить массив, бинарное поисковое дерево и AVL-дерево
void SetupLists(BinSTree<int>& Tree1, AVLTree<int>& Tree2,
    int A[], int n) {
    int i;
    srand(time(0));
    for (i = 0; i < n; i++) {
        A[i] = rand() % 1000;       //запомнить случайное число в массиве А
        Tree1.Insert(A[i]);         //включить его в бинарное дерево поиска
        Tree2.Insert(A[i]);         //в AVL-дерево
    }
}


//расчёт длины поиска элемента
template <class T>
void PathLenght(TreeNode<T>* t, long& totallenght, int item) {
    if (t == NULL || t->data == item)   //если пустой узел или найден ключ
        return;
    else {
        totallenght++;                  //пройден ещё один узел
        if (item < t->data)             //выбор направления поиска
            PathLenght(t->Left(), totallenght, item);
        else PathLenght(t->Right(), totallenght, item);
    }
}


int main() {
    setlocale(LC_ALL, "rus");
    long total_BST = 0, total_AVL = 0;      //длина поиска деревьев
    int n = 10;                             //кол-во узлов
    ofstream fout;                          //файл с результатом
    fout.open("Result.txt");
    int* A = new int[n] {805, 624, 756, 286, 176, 624, 689, 165, 496, 300};
    BinSTree<int> binT;                     //бинарное дерево поиска
    AVLTree<int> avlT, avlT_c;              //AVL-дерево
    

    //ручная вставка
    for (int i = 0; i < n; i++) {
        binT.Insert(A[i]);
        avlT.Insert(A[i]);
    }

    //отображаем очередь
    cout << "Очередь: " << endl; fout << "Очередь: " << endl;
    for (int i = 0; i < n; i++) {
        if (i % 10 == 0 && i >= 10) cout << endl;   //10 элементов в строке
        cout << A[i] << " ; "; fout << A[i] << " ; ";
    }


    //вывод деревьев на экран
    cout << endl << "Bin " << endl;
    fout << endl << "Bin " << endl;
    binT.PrintTreeB(0);
    binT.PrintTreeBFile(0, "res.txt");
    cout << endl << "AVL " << endl;
    fout << endl << "AVL " << endl;
    avlT.PrintTreeB(0);
    avlT.PrintTreeBFile(0, "res.txt");
    avlT_c = avlT;


    //удаление листового узла
    int key = 496;
    avlT_c.Delete(key);
    cout << endl << "Удалить список " << key << "): " << endl;
    fout << endl << "Удалить список" << key << "): " << endl;
    avlT_c.PrintTreeB(0);
    avlT_c.PrintTreeBFile(0, "res.txt");


    //удаление промежуточного узла
    key = 300;
    avlT_c.Delete(key);
    cout << endl << "Удалить центральный " << key << "): " << endl;
    fout << endl << "Удалить центральный " << key << "): " << endl;
    avlT_c.PrintTreeB(0);
    avlT_c.PrintTreeBFile(0, "res.txt");


    //удаление корневого узла
    key = 624;
    avlT_c.Delete(key);
    cout << endl << "Удалить корень " << key << "): " << endl;
    fout << endl << "Удалить корень " << key << "): " << endl;
    avlT_c.PrintTreeB(0);
    avlT_c.PrintTreeBFile(0, "res.txt");


    /* программа вычисления средней длины поиска*/
    int n2 = 1000;                      //100 или 1000
    total_AVL = total_BST = 0;          //обнуляем переменные результата
    A = new int[n2];                    //перезадаём массив
    SetupLists(binT, avlT_c, A, n2);    //заполняем деревья
    
    for (int i = 0; i < n2; i++) {
        PathLenght(binT.GetRoot(), total_BST, A[i]);
        PathLenght(avlT_c.GetRoot(), total_AVL, A[i]);
    }

    cout << "Размер = " << n2 << endl;
    fout << "Размер = " << n2 << endl;
    cout << "Глубина Bin = " << binT.DepthB() << endl;
    cout << "Нахождение длины = " << float(total_BST) / n2 << endl;
    cout << "Глибина AVL = " << avlT_c.DepthB() << endl;
    cout << "Нахождение длины AVL = " << float(total_AVL) / n2 << endl;
    fout << "Глубина Bin = " << binT.DepthB() << endl;
    fout << "Нахождение длины = " << float(total_BST) / n2 << endl;
    fout << "Глубина AVL = " << avlT_c.DepthB() << endl;
    fout << "Нахождение длины AVL = " << float(total_AVL) / n2 << endl;


    delete[] A;

    fout.close();


    return 0;
}
