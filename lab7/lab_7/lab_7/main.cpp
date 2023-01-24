#include <iostream>
#include <fstream>
#include <clocale>
#include <time.h>
#include "Sort.h"
#include "Heap.h"
using namespace std;

//���������� �������
int* create_mas(int n, int min, int max) {
    int* res = new int[n];
    srand(time(0)); //����� ������� �������
    for (int i = 0; i < n; i++) {
        res[i] = rand() % (max - min) + min; //��������� � ���������
    }
    return res;
}

//������ �������
void print_mas(int* arr, int n, ostream& strm) {
    for (int i = 0; i < n; i++) {
        if (i != 0 && i % 8 == 0) { //10 ��������� � ������
            strm << endl;
        }
        strm << arr[i] << " ";
    }
    strm << endl;
}

//������ ��������
void print_heap(Heap<int>& heap, ostream& strm) {
    for (int i = 0; i < heap.ListSize(); i++) {
        strm << "[" << i << "]:" << heap[i] << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Rus");

    ofstream fout;
    fout.open("Result.txt");


    //������ � ��������� ������
    int n = 4; //������
    int* arr1 = create_mas(n, 100, 1000);
    //������ ��������� �������
    cout << "��������� ������ (n=20)" << endl;
    fout << "��������� ������ (n=20)" << endl;
    print_mas(arr1, n, cout);
    print_mas(arr1, n, fout);
    //��������� �������������
    Sort(arr1, n);
    //������ ��������� �������
    cout << "�������� ������" << endl;
    fout << "�������� ������" << endl;
    print_mas(arr1, n, cout);
    print_mas(arr1, n, fout);
    cout << endl;
    fout << endl;

    //������ � ��������� ������
    int n2 = 100;
    int* arr2 = create_mas(n2, 100, 1000);
    //������ ��������� �������
    cout << "��������� ������ (n=200)" << endl;
    fout << "��������� ������ (n=200)" << endl;
    print_mas(arr2, n2, cout);
    print_mas(arr2, n2, fout);
    //��������� �������������
    Sort(arr2, n2);
    //������ ��������� �������
    cout << "�������� ������" << endl;
    fout << "�������� ������" << endl;
    print_mas(arr2, n2, cout);
    print_mas(arr2, n2, fout);
    cout << endl;
    fout << endl;

    
   
    //��������� ������ ��������
    Heap<int> h1(arr2, n2), h2(n2);
    //�������� ���������� ��������
    cout << "�������� 1: " << endl;
    fout << "�������� 1: " << endl;
    print_heap(h1, cout);
    print_heap(h1, fout);

    while (!h1.ListEmpty()) { //���� � 1-� �������� ���� ��������
        int buf = h1.Delete(); //��������� ������� �� 1-�
        h2.Insert(buf); //� ��������� �� 2-�
    }

    //�������� ���������� ��������
    cout << "�������� 2: " << endl;
    fout << "�������� 2: " << endl;
    print_heap(h2, cout);
    print_heap(h2, fout);
    //����������� ������
    delete[] arr1;
    delete[] arr2;
    return 0;

     
}
