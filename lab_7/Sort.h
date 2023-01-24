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


//турнирная сортировка
template <class T>
void TourmentSort(T a[], int n) {
    
    DataNode<T>* tree; // корень дерева
    DataNode<T> item;
    
    // минимальная степень двойки, большая или равная п
    int bottomRowSize;
    
    // число узлов в полном дереве, нижний ряд которого
    // имеет bottomRowSize узлов
    int treesize;
    
    // начальный индекс нижнего ряда узлов
    int loadindex;
    int i, j = 0;
    
    // определить требуемый размер памяти для нижнего ряда узлов
    bottomRowSize = PowerOfTwo(n);
    
    // вычислить размер дерева и динамически создать его узлы
    treesize = pow(2, bottomRowSize + 1) - 1;
    tree = new DataNode<T>[treesize];
    
    //вычисляем начальный индекс элементов
    loadindex = treesize - pow(2, bottomRowSize);
    
    // скопировать массив в дерево объектов типа DataNode
    for (i = loadindex; i < treesize; i++) {
        item.index = i;
        if (j < n) {                    //если индекс не превышает кол-во элементов
            item.active = true;         //определяем, что элемент участвует
            item.data = a[j++];         //копируем данные
        }
        else item.active = false;       //иначе элемент не участвует
        tree[i] = item;
    }
    
    // выполнить начальные сравнения для определения наименьшего элемента
    i = loadindex;
    while (i > 0) {
        j = i;                  //определяем индекс начала уровня
        while (j < 2 * i) {     // обработать пары соревнующихся
        // проведение матча. сравнить tree [j] с его соперником tree [j + 1]
        // скопировать победителя в родительский узел
            (!tree[j + 1].active || tree[j] < tree[j + 1]) ?
                tree[(j - 1) / 2] = tree[j] : tree[(j - 1) / 2] = tree[j + 1];
            j += 2;
        }
        // перейти к следующему кругу соревнования (родительский уровень)
        i = (i - 1) / 2;
    }
    
    // обработать оставшиеся n-1 элементов, и обновить
    // дерево, разрешив сопернику победителя снова войти в турнир
    for (i = 0; i < n - 1; i++) {
        a[i] = tree[0].data; //копируем победителя
        tree[tree[0].index].active = false; //сделаем победителя неактивным
        UpdateTree(tree, tree[0].index);
    }
    
    // скопировать последнее значение в массив
    a[n - 1] = tree[0].data;

}
#endif // SORT_H
