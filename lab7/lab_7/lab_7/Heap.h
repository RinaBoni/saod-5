#ifndef HEAP_H
#define HEAP_H
#include <iostream>
//перечень кодов ошибок
enum class HeapError {
    Size, NO_ELEMENTS, Index, isFull, isEmpty
};

//класс пирамиды
template <class T>
class Heap {
private:
    // hlist указывает на массив, который может быть динамически создан
    // конструктором (inArray == 0) или передан как параметр (inArray == 1)
    T* hlist;
    int inArray;

    // максимальный и текущий размеры пирамиды
    int maxheapsize;

    // определяет конец списка
    int heapsize; 


    //утилита восстановления пирамидальной структуры начиная с индекса i,
    //поднятие вверх по дереву,
    //менять элементы мечтаит, если сын меньше родителя
    void FilterUp(int i) {
        int currentpos, parentpos; //currentpos - индекс текущей позиции на пути предков
        T target;                  //target - вставляемое значение, для которого выбирается
                                   // правильная позиция в пирамиде
        currentpos = i;
        parentpos = (i - 1) / 2;
        target = this->hlist[i];
        
        while (currentpos != 0) {  // подниматься к корню по пути родителей
          
            if (this->hlist[parentpos] <= target)       // если родитель <= target, то все в порядке.
                break;
            else {
                // поменять местами родителя с сыном и обновить индексы
                // для проверки следующего родителя
                // переместить данные из родительской позиции в текущую.
                // назначить родительскую позицию текущей.
                // проверить следующего родителя
                this->hlist[currentpos] = hlist[parentpos];
                currentpos = parentpos;
                parentpos = (currentpos - 1) / 2;
            }

        }
        this->hlist[currentpos] = target;       // правильная позиция найдена. поместить туда target
    }

    //восстановление пирамидальности от определённого индекса
    //для метода удаления
    void FilterDown(int i) {
        int currentpos, childpos;
        T target;

        // начать с узла і и присвоить его значение переменной target
        currentpos = i;
        target = this->hlist[i];

        // вычислить индекс левого сына и начать движение вниз по пути,
        // проходящему через меньших сыновей до конца списка
        childpos = 2 * i + 1;
        while (childpos < this->heapsize) { // пока не конец списка
            // индекс правого сына равен childpos+1. присвоить переменной
            // childpos индекс наименьшего из двух сыновей
            if ((childpos + 1 < this->heapsize) &&
                (this->hlist[childpos + 1] <= this->hlist[childpos]))
                childpos = childpos + 1;
           
            // если родитель меньше сына, пирамида в порядке. выход
            if (target <= this->hlist[childpos])
                break;
            else {
                // переместить значение меньшего сына в родительский узел.
                // теперь позиция меньшего сына не занята
                this->hlist[currentpos] = this->hlist[childpos];

                // обновить индексы и продолжить сканирование
                currentpos = childpos;
                childpos = 2 * currentpos + 1;
            }
        }
        this->hlist[currentpos] = target;
    }

public:
    // конструкторы и деструктор
    Heap(int maxsize) {
        this->maxheapsize = maxsize;
        this->heapsize = 0;
        this->hlist = new T[maxsize];
        this->inArray = false;
    }


    // создать пустую пирамиду
    Heap(T arr[], int n) {
        if (n <= 0) // если является недопустимым размером массива
            throw HeapError::Size;
       
        // использовать п для установки размера пирамиды и максимального размера пирамиды.
        // копировать массив arr в список пирамиды
        this->maxheapsize = n;
        this->heapsize = n;
        
        this->hlist = arr;
        // присвоить переменной currentpos индекс последнего родителя.
        // вызывать FilterDown в цикле с индексами currentpоз…0
        int currentpos = (this->heapsize - 2) / 2;
        while (currentpos >= 0) {
            // выполнить условие пирамидальности для поддерева
            // с корнем hlist[currentpos)
            FilterDown(currentpos);
            currentpos--;
        }
       
        // присвоить флажку inArray значение True
        this->inArray = true;
    }


    // преобразовать arr в пирамиду
    Heap(const Heap<T>& H) {
        this = H;
    }


    //дестрктор
    ~Heap(void) {
        ClearList();
        delete[] this->hlist;
    }


    // перегруженные операторы: "=", "[]"
    Heap<T> operator= (const Heap <T> heap) {
        int n = heap.maxheapsize;
        this->heapsize = heap.heapsize;
        this->maxheapsize = n;
        this->hlist = new T[n];
       
        if (this->hlist == NULL)
            throw HeapError::NO_ELEMENTS;
        
        // копировать элементы массива в текущий объект
        T* srcptr = heap.hlist; // адрес начала источника
        T* destptr = this->hlist; // адрес начала копии
        
        while (n--) // копировать список
            *destptr++ = *srcptr++;
        return *this;
    }


    //операция индексации
    const T operator[] (int i) {
        if (i<0 || i>(this->heapsize - 1)) //если индекс вне диапазона
            throw HeapError::Index;
        return this->hlist[i];
    }


    // методы обработки списков
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
        // проверить, заполнена ли пирамида и выйти, если да
        if (this->heapsize == this->maxheapsize)
            throw HeapError::isFull;
        
        // записать элемент в конец пирамиды и увеличить heapsize.
        // вызвать FilterUp для восстановления пирамидального упорядочения
        this->hlist[this->heapsize] = item;
        FilterUp(this->heapsize);
        this->heapsize++;
    }


    T Delete(void) {
        T tempitem;
        
        //проверить, пуста ли пирамида
        if (heapsize == 0)
            throw HeapError::isEmpty;
        
        // копировать корень в tempitem. заменить корень последним элементом
        // пирамиды и произвести декремент переменной heapsize
        tempitem = hlist[0];
        hlist[0] = hlist[heapsize - 1];
        heapsize--;
        
        // вызвать FilterDown для установки нового значения корня
        FilterDown(0);
        
        // возвратить исходное значение корня
        return tempitem;
    }


    void ClearList(void) {
        this->hlist = new T[maxheapsize];
        this->heapsize = 0;
    }
};

#endif // HEAP_H
