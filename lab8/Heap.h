#ifndef HEAP_H
#define HEAP_H
#include <iostream>
//�������� ����� ������
enum class HeapError {
    Size, NO_ELEMENTS, Index, isFull, isEmpty
};

//����� ��������
template <class T>
class Heap {
private:
    // hlist ��������� �� ������, ������� ����� ���� ����������� ������
    // ������������� (inArray == 0) ��� ������� ��� �������� (inArray == 1)
    T* hlist;
    int inArray;

    // ������������ � ������� ������� ��������
    int maxheapsize;

    // ���������� ����� ������
    int heapsize; 


    //������� �������������� ������������� ��������� ������� � ������� i,
    //�������� ����� �� ������,
    //������ �������� �������, ���� ��� ������ ��������
    void FilterUp(int i) {
        int currentpos, parentpos; //currentpos - ������ ������� ������� �� ���� �������
        T target;                  //target - ����������� ��������, ��� �������� ����������
                                   // ���������� ������� � ��������
        currentpos = i;
        parentpos = (i - 1) / 2;
        target = this->hlist[i];
        
        while (currentpos != 0) {  // ����������� � ����� �� ���� ���������
          
            if (this->hlist[parentpos] <= target)       // ���� �������� <= target, �� ��� � �������.
                break;
            else {
                // �������� ������� �������� � ����� � �������� �������
                // ��� �������� ���������� ��������
                // ����������� ������ �� ������������ ������� � �������.
                // ��������� ������������ ������� �������.
                // ��������� ���������� ��������
                this->hlist[currentpos] = hlist[parentpos];
                currentpos = parentpos;
                parentpos = (currentpos - 1) / 2;
            }

        }
        this->hlist[currentpos] = target;       // ���������� ������� �������. ��������� ���� target
    }

    //�������������� ��������������� �� ������������ �������
    //��� ������ ��������
    void FilterDown(int i) {
        int currentpos, childpos;
        T target;

        // ������ � ���� � � ��������� ��� �������� ���������� target
        currentpos = i;
        target = this->hlist[i];

        // ��������� ������ ������ ���� � ������ �������� ���� �� ����,
        // ����������� ����� ������� ������� �� ����� ������
        childpos = 2 * i + 1;
        while (childpos < this->heapsize) { // ���� �� ����� ������
            // ������ ������� ���� ����� childpos+1. ��������� ����������
            // childpos ������ ����������� �� ���� �������
            if ((childpos + 1 < this->heapsize) &&
                (this->hlist[childpos + 1] <= this->hlist[childpos]))
                childpos = childpos + 1;
           
            // ���� �������� ������ ����, �������� � �������. �����
            if (target <= this->hlist[childpos])
                break;
            else {
                // ����������� �������� �������� ���� � ������������ ����.
                // ������ ������� �������� ���� �� ������
                this->hlist[currentpos] = this->hlist[childpos];

                // �������� ������� � ���������� ������������
                currentpos = childpos;
                childpos = 2 * currentpos + 1;
            }
        }
        this->hlist[currentpos] = target;
    }

public:
    // ������������ � ����������
    Heap(int maxsize) {
        this->maxheapsize = maxsize;
        this->heapsize = 0;
        this->hlist = new T[maxsize];
        this->inArray = false;
    }


    // ������� ������ ��������
    Heap(T arr[], int n) {
        if (n <= 0) // ���� �������� ������������ �������� �������
            throw HeapError::Size;
       
        // ������������ � ��� ��������� ������� �������� � ������������� ������� ��������.
        // ���������� ������ arr � ������ ��������
        this->maxheapsize = n;
        this->heapsize = n;
        
        this->hlist = arr;
        // ��������� ���������� currentpos ������ ���������� ��������.
        // �������� FilterDown � ����� � ��������� currentp��0
        int currentpos = (this->heapsize - 2) / 2;
        while (currentpos >= 0) {
            // ��������� ������� ��������������� ��� ���������
            // � ������ hlist[currentpos)
            FilterDown(currentpos);
            currentpos--;
        }
       
        // ��������� ������ inArray �������� True
        this->inArray = true;
    }


    // ������������� arr � ��������
    Heap(const Heap<T>& H) {
        this = H;
    }


    //���������
    ~Heap(void) {
        ClearList();
        delete[] this->hlist;
    }


    // ������������� ���������: "=", "[]"
    Heap<T> operator= (const Heap <T> heap) {
        int n = heap.maxheapsize;
        this->heapsize = heap.heapsize;
        this->maxheapsize = n;
        this->hlist = new T[n];
       
        if (this->hlist == NULL)
            throw HeapError::NO_ELEMENTS;
        
        // ���������� �������� ������� � ������� ������
        T* srcptr = heap.hlist; // ����� ������ ���������
        T* destptr = this->hlist; // ����� ������ �����
        
        while (n--) // ���������� ������
            *destptr++ = *srcptr++;
        return *this;
    }


    //�������� ����������
    const T operator[] (int i) {
        if (i<0 || i>(this->heapsize - 1)) //���� ������ ��� ���������
            throw HeapError::Index;
        return this->hlist[i];
    }


    // ������ ��������� �������
    int ListSize() const {
        return this->heapsize;
    }


    int MaxSize() const {
        return this->maxheapsize;
    }


    bool ListEmpty() const {
        return (this->heapsize <= 0);
    }


    bool ListFull() const {
        return (this->heapsize == this->maxheapsize);
    }


    void Insert(const T& item) {
        // ���������, ��������� �� �������� � �����, ���� ��
        if (this->heapsize == this->maxheapsize)
            throw HeapError::isFull;
        
        // �������� ������� � ����� �������� � ��������� heapsize.
        // ������� FilterUp ��� �������������� �������������� ������������
        this->hlist[this->heapsize] = item;
        FilterUp(this->heapsize);
        this->heapsize++;
    }


    T Delete(void) {
        T tempitem;
        
        //���������, ����� �� ��������
        if (heapsize == 0)
            throw HeapError::isEmpty;
        
        // ���������� ������ � tempitem. �������� ������ ��������� ���������
        // �������� � ���������� ��������� ���������� heapsize
        tempitem = hlist[0];
        hlist[0] = hlist[heapsize - 1];
        heapsize--;
        
        // ������� FilterDown ��� ��������� ������ �������� �����
        FilterDown(0);
        
        // ���������� �������� �������� �����
        return tempitem;
    }


    void ClearList(void) {
        this->hlist = new T[maxheapsize];
        this->heapsize = 0;
    }
};

#endif // HEAP_H
