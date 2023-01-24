#ifndef AVLTREE_H
#define AVLTREE_H
#include "BinSTree.h"
#include "AVLTreeNode.h"

template <class T>
class AVLTree : public BinSTree<T> {
private:
    // выделение памяти
    AVLTreeNode<T>* GetAVLTreeNode(const T& item, AVLTreeNode<T>* lptr, AVLTreeNode<T>* rptr);
    AVLTreeNode<T>* CopyTree(AVLTreeNode<T>* t);

    //вращение влево
    AVLTreeNode<T>* RotateLeft(AVLTreeNode<T>*& node); 

    //вращение вправо
    AVLTreeNode<T>* RotateRight(AVLTreeNode<T>*& node); 

    //////////функции для определения балансировки//////////

    //вычисление высоты узла
    int Height(AVLTreeNode<T>* node); 

    //вычисление баланса узла
    int BFactor(AVLTreeNode<T>* node); 

    //процедура пересчёта баланса узла
    void FixBF(AVLTreeNode<T>* node); 

    //функция балансировки
    AVLTreeNode<T>* Balance(AVLTreeNode<T>* p); 

    //поиск минимального узла
    AVLTreeNode<T>* FindMin(AVLTreeNode<T>* p); 

    //удалить минимальный элемент
    AVLTreeNode<T>* RemoveMin(AVLTreeNode<T>* p);

    //рекурсивная функция добавления узла по ключу
    AVLTreeNode<T>* Add(AVLTreeNode<T>* p, T x); 

    //рекурсивная функция удаления узла по ключу
    AVLTreeNode<T>* Remove(AVLTreeNode<T>* p, int k); 

public:
    
    // конструкторы
    AVLTree();
    AVLTree(const AVLTree<T>& tree);
    
    // оператор присваивания
    AVLTree<T>& operator= (const AVLTree<T>& tree);
    
    // стандартные методы обработки списков
    virtual void Insert(const T& item);
    virtual void Delete(const T& item);
};

template<class T>
inline AVLTreeNode<T>* AVLTree<T>::GetAVLTreeNode(const T& item, AVLTreeNode<T>* lptr, AVLTreeNode<T>* rptr) {
    AVLTreeNode<T>* p;
    p = new AVLTreeNode<T>(item, lptr, rptr);
    if (p == NULL) {
        cerr << "Ошибка выделения памяти!" << endl;
        exit(1);
    }
    return p;
}


//функция копирования класса
template<class T>
inline AVLTreeNode<T>* AVLTree<T>::CopyTree(AVLTreeNode<T>* t) {
   
    AVLTreeNode<T>* newlptr, * newrptr, * newnode;
    i
        f (t == NULL)                       //если дерево пустое
        return NULL;
    
    //функция СоруTree проверяет наличие левого потомка
    if (t->Left() != NULL)
        newlptr = CopyTree(t->Left());      //если он есть, создается его копия
    else newlptr = NULL;
    if (t->Right() != NULL)
        newrptr = CopyTree(t->Right());
    else newrptr = NULL;

    //построика нового дерева снизу вверх
    newnode = GetAVLTreeNode(t->data, newlptr, newrptr);
    newnode->balanceFactor = t->GetBF();    //передаём баланс
    return newnode;                         //вернуть указатель на вновь созданное дерево
}


//вращение вправо
template <class T>
AVLTreeNode<T>* AVLTree<T>::RotateRight(AVLTreeNode<T>*& p) {
    AVLTreeNode<T>* q = p->LeftLink;        //итоговый узел = левый сын родителя
    p->LeftLink = (q->RightLink);           //левый сын теперь правый потомок сына
    q->RightLink = (p);                     //правый потомок сына = родитель

    //пересчитываем балансы узлов
    this->FixBF(p);
    this->FixBF(q);
    return q;                               //возвращаем повёрнутый узел
}


//вправо влево
template <class T>
AVLTreeNode<T>* AVLTree<T>::RotateLeft(AVLTreeNode<T>*& p) {
    AVLTreeNode<T>* q = p->RightLink;       //итоговый узел = правый сын родителя
    p->RightLink = (q->LeftLink);           //правый сын теперь левый потомок сына
    q->LeftLink = (p);                      //левый потомок сына = родитель

    //пересчитываем балансы узлов
    this->FixBF(p);
    this->FixBF(q);
    return q;                               //возвращаем повёрнутый узел
}


//вычисление высоты узла
template <class T>
int AVLTree<T>::Height(AVLTreeNode<T>* node) {
    if (node != NULL) return node->GetBF();  //если узел не пустой
    return 0;
}


//вычисление баланса узла
template <class T>
int AVLTree<T>::BFactor(AVLTreeNode<T>* node) {

    //возвращаем баланс как разницу высот
    return this->Height(node->RightLink) - this->Height(node->LeftLink);
}


//процедура пересчёта баланса узла
template <class T>
void AVLTree<T>::FixBF(AVLTreeNode<T>* node) {
    int hl = this->Height(node->LeftLink);              //высота левого потомка
    int hr = this->Height(node->RightLink);             //высота правого потомка
    node->balanceFactor = ((hl > hr ? hl : hr) + 1);    //обновляем поле
}


//функция балансировки узла
template <class T>
AVLTreeNode<T>* AVLTree<T>::Balance(AVLTreeNode<T>* p) {
    this->FixBF(p);                                      //обновляем высоту
    
    if (this->BFactor(p) == 2) {
        if (this->BFactor(p->RightLink) < 0)
            p->RightLink = (this->RotateRight(p->RightLink));
        return this->RotateLeft(p);                      //вращаем влево
    }
    
    if (this->BFactor(p) == -2) {
        if (this->BFactor(p->LeftLink) > 0)
            p->LeftLink = (this->RotateLeft(p->LeftLink));
        return this->RotateRight(p);                     //вращаем вправо
    }
    
    return p;
}


//рекурсивная функция добавления узла
template <class T>
AVLTreeNode<T>* AVLTree<T>::Add(AVLTreeNode<T>* p, T x) { // вставка ключа k в дерево с корнем p
    if (!p) return GetAVLTreeNode(x, NULL, NULL);

    if (x < p->data)                                    //выбор направления вставки
        p->LeftLink = (this->Add(p->LeftLink, x));
    else
        p->RightLink = (this->Add(p->RightLink, x));

    return this->Balance(p);                            //возвращаем сбалансированный узел
}


//поиск минимального узла
template <class T>
AVLTreeNode<T>* AVLTree<T>::FindMin(AVLTreeNode<T>* p) {
    return p->LeftLink ? this->FindMin(p->LeftLink) : p;
}


//рекурсивная функция удаления узла по ключу
template <class T>
AVLTreeNode<T>* AVLTree<T>::Remove(AVLTreeNode<T>* p, int k) {
    if (!p) return 0;                                   //если нечего удалять
    
    if (k < p->data)                                    //выбор направления удаления
        p->LeftLink = this->Remove(p->LeftLink, k);
    else if (k > p->data)
        p->RightLink = this->Remove(p->RightLink, k);
    else {
        AVLTreeNode<T>* q = p->LeftLink;
        AVLTreeNode<T>* r = p->RightLink;
        if (!r) return q;                               //если нет правого узла, то возвращаем левый
        AVLTreeNode<T>* min = this->FindMin(r);         //ищем минимальный узел
        min->RightLink = this->RemoveMin(r);            //удаляем минимальный узел и сохраняем его правого потомка
        min->LeftLink = q;                              //присоединяем левого потомка удаляемого узла
        if (p != this->root) this->FreeTreeNode(p);     //если удаляемый узел не корень
        else {                                          //иначе переопределяем корень
            this->root = min;
            this->FreeTreeNode(p);
        }
        return this->Balance(min);                      //возвращаем сбалансированный новый узел
    }
    return this->Balance(p);                            //возвращаем обновлённый узел
}


//удаление узла с минимальным ключом из дерева p
template <class T>
AVLTreeNode<T>* AVLTree<T>::RemoveMin(AVLTreeNode<T>* p) {
    
    if (p->LeftLink == NULL)                            //если нет левого потомка
        return p->RightLink;                            //то возвращаем правого
    
    p->LeftLink = this->RemoveMin(p->LeftLink);         //спускаемся влево
    
    return this->Balance(p);                            //возвращаем сбалансированный узел
}


//пустой конструктор
template<class T>
inline AVLTree<T>::AVLTree() {
    this->size = 0; this->root = NULL; this->current = NULL;
}


//конструктор копирования
template<class T>
inline AVLTree<T>::AVLTree(const AVLTree<T>& tree) {
    this = tree;
}


//переопределение присваивания
template<class T>
inline AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& tree) {
    if (this == &tree) return *this;
    
    this->ClearList();                                  //очистка дерева
    this->root = this->CopyTree((AVLTreeNode<T>*)tree.root); //копируем корень дерева
    this->current = this->root;                         //смещаем указатель на корень
    this->size = tree.size;                             //копируем кол-во элементов
    
    return *this;                                       //возвращаем
}


//метод вставки
template<class T>
inline void AVLTree<T>::Insert(const T& item) {
    this->root = this->Add((AVLTreeNode<T>*)this->root, item);
    this->size++;       //увеличиваем счётчик
}


//метод удаления
template<class T>
inline void AVLTree<T>::Delete(const T& item) {
    this->root = this->Remove((AVLTreeNode<T>*)this->root, item);
    this->size--;       //уменьшаем счётчик
}


//горизонтальная печать дерева на экран
template <class T>
void PrintTreeB(AVLTreeNode<T>* t, int level) {
    if (t != NULL) {                            //пока указатель не пуст
        PrintTree(t->Right(), level + 1);       //печатаем правое поддерево
        IndentBlanks(6 * level);                //вставка пробелов и выравнивание
        cout << t->data << endl;
        PrintTree(t->Left(), level + 1);        //печатаем левое поддерево
    }
}


//горизонтальная печать дерева в файл
template <class T>
void PrintTreeFile(AVLTreeNode<T>* t, int level, string s1) {
    if (t != NULL) {
        ofstream f(s1, ios_base::app);
        PrintTreeFile(t->Right(), level + 1, s1); //печатаем правое поддерево
        for (int i = 0; i < 6 * level; i++) {
            f << " ";
        }
        f << t->data << endl;
        PrintTreeFile(t->Left(), level + 1, s1); //печатаем левое поддерево
    }
}

#endif 
