#ifndef SORT_H
#define SORT_H
#include <math.h>
#include "Heap.h"
//класс узла
template <class T>
class DataNode
{
public:
    T data; //данные
    int index; //индекс
    bool active; //состояние активности

    friend bool operator < (const DataNode<T>& X, const DataNode<T>& Y) {
        return X.data < Y.data; //сравнение данных
    }
};

int PowerOfTwo(int n) {
    int res = log2(n);
    return res + (log2(n) > res);
}

//обновление дерева
template <class T>
void UpdateTree(DataNode<T>* tree, int i) {
    int j; //индекс сравниваемого элемента
    // определить соперника победителя. позволить ему продолжить
    // турнир, копируя его в родительский узел.
    if (i % 2 == 0)
        tree[(i - 1) / 2] = tree[i - 1]; // соперник - левый узел
    else
        tree[(i - 1) / 2] = tree[i + 1]; // соперник - правый узел
    // переиграть те матчи, в которых принимал участие
    // только что исключенный из турнира игрок
    i = (i - 1) / 2;
    while (i > 0) {
        //  правый или левый узел?
        (i % 2 == 0) ?
            j = i - 1 : j = i + 1;
        // проверить, является  активным
        if (!tree[i].active || !tree[j].active)
            (tree[i].active) ?
            tree[(i - 1) / 2] = tree[i] : tree[(i - 1) / 2] = tree[j];
        // устроить соревнование.
        // победителя скопировать в родительский узел
        else
            (tree[i] < tree[j]) ?
            tree[(i - 1) / 2] = tree[i] : tree[(i - 1) / 2] = tree[j];
        // перейти к следующему кругу соревнования (родительский уровень)
        i = (i - 1) / 2;
    } //турнир с новым соперником закончен
}


template <class T>
void HeapSort(T a[],int n) {
    // конструктор преобразующий массив а в пирамиду
    Heap<T> H(a,n);
    T elt;
    for (int i = n - 1; i >= 0;i--) {
        // исключить наименьший элемент и заполнить его в A[i]
        elt = H.Delete();
        a[i] = elt;
    }
}
#endif // SORT_H
