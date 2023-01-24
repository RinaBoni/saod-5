#ifndef SORT_H
#define SORT_H
#include <math.h>
#include "Heap.h"
//����� ����
template <class T>
class DataNode
{
public:
    T data; //������
    int index; //������
    bool active; //��������� ����������

    friend bool operator < (const DataNode<T>& X, const DataNode<T>& Y) {
        return X.data < Y.data; //��������� ������
    }
};

int PowerOfTwo(int n) {
    int res = log2(n);
    return res + (log2(n) > res);
}

//���������� ������
template <class T>
void UpdateTree(DataNode<T>* tree, int i) {
    int j; //������ ������������� ��������
    // ���������� ��������� ����������. ��������� ��� ����������
    // ������, ������� ��� � ������������ ����.
    if (i % 2 == 0)
        tree[(i - 1) / 2] = tree[i - 1]; // �������� - ����� ����
    else
        tree[(i - 1) / 2] = tree[i + 1]; // �������� - ������ ����
    // ���������� �� �����, � ������� �������� �������
    // ������ ��� ����������� �� ������� �����
    i = (i - 1) / 2;
    while (i > 0) {
        //  ������ ��� ����� ����?
        (i % 2 == 0) ?
            j = i - 1 : j = i + 1;
        // ���������, ��������  ��������
        if (!tree[i].active || !tree[j].active)
            (tree[i].active) ?
            tree[(i - 1) / 2] = tree[i] : tree[(i - 1) / 2] = tree[j];
        // �������� ������������.
        // ���������� ����������� � ������������ ����
        else
            (tree[i] < tree[j]) ?
            tree[(i - 1) / 2] = tree[i] : tree[(i - 1) / 2] = tree[j];
        // ������� � ���������� ����� ������������ (������������ �������)
        i = (i - 1) / 2;
    } //������ � ����� ���������� ��������
}


template <class T>
void HeapSort(T a[],int n) {
    // ����������� ������������� ������ � � ��������
    Heap<T> H(a,n);
    T elt;
    for (int i = n - 1; i >= 0;i--) {
        // ��������� ���������� ������� � ��������� ��� � A[i]
        elt = H.Delete();
        a[i] = elt;
    }
}
#endif // SORT_H
