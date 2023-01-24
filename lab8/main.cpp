#include <iostream>
#include <fstream>
#include <clocale>
#include <time.h>
#include "Sort.h"
#include "Heap.h"
using namespace std;

//заполнение массива
int* create_mas(int n, int min, int max) {
    int* res = new int[n];
    srand(time(0)); //задаЄм условие рандома
    for (int i = 0; i < n; i++) {
        res[i] = rand() % (max - min) + min; //заполн€ем в диапазоне
    }
    return res;
}

//печать массива
void print_mas(int* arr, int n, ostream& strm) {
    for (int i = 0; i < n; i++) {
        if (i != 0 && i % 8 == 0) { //10 элементов в строке
            strm << endl;
        }
        strm << arr[i] << " ";
    }
    strm << endl;
}

//печать пирамиды
void print_heap(Heap<int>& heap, ostream& strm) {
    for (int i = 0; i < heap.ListSize(); i++) {
        strm << "[" << i << "]:" << heap[i] << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Rus");

    ofstream fout;
    fout.open("Result.txt");


    //создаЄм и заполн€ем массив
    int n = 4; //размер
    int* arr1 = create_mas(n, 100, 1000);


    //печать исходного массива
    cout << "Ќачальный массив (n=4)" << endl;
    fout << "Ќачальный массив (n=4)" << endl;
    print_mas(arr1, n, cout);
    print_mas(arr1, n, fout);


    //сортируем пирамидальной
    HeapSort(arr1, n);


    //печать конечного массива
    cout << endl;
    fout << endl;
    cout << " онечный массив" << endl;
    fout << " онечный массив" << endl;
    print_mas(arr1, n, cout);
    print_mas(arr1, n, fout);
    cout << endl;
    fout << endl;
    cout << endl;
    fout << endl;


    //создаЄм и заполн€ем массив
    int n2 = 100;
    int* arr2 = create_mas(n2, 100, 1000);


    //печать исходного массива
    cout << "Ќачальный массив (n=100)" << endl;
    fout << "Ќачальный массив (n=100)" << endl;
    print_mas(arr2, n2, cout);
    print_mas(arr2, n2, fout);


    //сортируем пирамидальной
    HeapSort(arr2, n2);


    //печать конечного массива
    cout << endl;
    fout << endl;
    cout << " онечный массив" << endl;
    fout << " онечный массив" << endl;
    print_mas(arr2, n2, cout);
    print_mas(arr2, n2, fout);
    cout << endl;
    fout << endl;
    cout << endl;
    fout << endl;


    //заполн€ем первую пирамиду
    Heap<int> h1(arr1, n);
    Heap<int> h2(arr2, n2);


    //печатаем содержимое пирамиды
    cout << "ѕирамида 1: " << endl;
    fout << "ѕирамида 1: " << endl;
    print_heap(h1, cout);
    print_heap(h1, fout);


    //печатаем содержимое пирамиды
    cout << endl;
    fout << endl;
    cout << endl;
    fout << endl;
    cout << "ѕирамида 2: " << endl;
    fout << "ѕирамида 2: " << endl;
    print_heap(h2, cout);
    print_heap(h2, fout);


    //освобождаем пам€ть
    delete[] arr1;
    delete[] arr2;
    return 0;

     
}
