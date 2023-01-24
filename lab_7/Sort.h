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


//��������� ����������
template <class T>
void TourmentSort(T a[], int n) {
    
    DataNode<T>* tree; // ������ ������
    DataNode<T> item;
    
    // ����������� ������� ������, ������� ��� ������ �
    int bottomRowSize;
    
    // ����� ����� � ������ ������, ������ ��� ��������
    // ����� bottomRowSize �����
    int treesize;
    
    // ��������� ������ ������� ���� �����
    int loadindex;
    int i, j = 0;
    
    // ���������� ��������� ������ ������ ��� ������� ���� �����
    bottomRowSize = PowerOfTwo(n);
    
    // ��������� ������ ������ � ����������� ������� ��� ����
    treesize = pow(2, bottomRowSize + 1) - 1;
    tree = new DataNode<T>[treesize];
    
    //��������� ��������� ������ ���������
    loadindex = treesize - pow(2, bottomRowSize);
    
    // ����������� ������ � ������ �������� ���� DataNode
    for (i = loadindex; i < treesize; i++) {
        item.index = i;
        if (j < n) {                    //���� ������ �� ��������� ���-�� ���������
            item.active = true;         //����������, ��� ������� ���������
            item.data = a[j++];         //�������� ������
        }
        else item.active = false;       //����� ������� �� ���������
        tree[i] = item;
    }
    
    // ��������� ��������� ��������� ��� ����������� ����������� ��������
    i = loadindex;
    while (i > 0) {
        j = i;                  //���������� ������ ������ ������
        while (j < 2 * i) {     // ���������� ���� �������������
        // ���������� �����. �������� tree [j] � ��� ���������� tree [j + 1]
        // ����������� ���������� � ������������ ����
            (!tree[j + 1].active || tree[j] < tree[j + 1]) ?
                tree[(j - 1) / 2] = tree[j] : tree[(j - 1) / 2] = tree[j + 1];
            j += 2;
        }
        // ������� � ���������� ����� ������������ (������������ �������)
        i = (i - 1) / 2;
    }
    
    // ���������� ���������� n-1 ���������, � ��������
    // ������, �������� ��������� ���������� ����� ����� � ������
    for (i = 0; i < n - 1; i++) {
        a[i] = tree[0].data; //�������� ����������
        tree[tree[0].index].active = false; //������� ���������� ����������
        UpdateTree(tree, tree[0].index);
    }
    
    // ����������� ��������� �������� � ������
    a[n - 1] = tree[0].data;

}
#endif // SORT_H
