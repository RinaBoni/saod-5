#ifndef AVLTREE_H
#define AVLTREE_H
#include "BinSTree.h"
#include "AVLTreeNode.h"

template <class T>
class AVLTree : public BinSTree<T> {
private:
    // ��������� ������
    AVLTreeNode<T>* GetAVLTreeNode(const T& item, AVLTreeNode<T>* lptr, AVLTreeNode<T>* rptr);
    AVLTreeNode<T>* CopyTree(AVLTreeNode<T>* t);

    //�������� �����
    AVLTreeNode<T>* RotateLeft(AVLTreeNode<T>*& node); 

    //�������� ������
    AVLTreeNode<T>* RotateRight(AVLTreeNode<T>*& node); 

    //////////������� ��� ����������� ������������//////////

    //���������� ������ ����
    int Height(AVLTreeNode<T>* node); 

    //���������� ������� ����
    int BFactor(AVLTreeNode<T>* node); 

    //��������� ��������� ������� ����
    void FixBF(AVLTreeNode<T>* node); 

    //������� ������������
    AVLTreeNode<T>* Balance(AVLTreeNode<T>* p); 

    //����� ������������ ����
    AVLTreeNode<T>* FindMin(AVLTreeNode<T>* p); 

    //������� ����������� �������
    AVLTreeNode<T>* RemoveMin(AVLTreeNode<T>* p);

    //����������� ������� ���������� ���� �� �����
    AVLTreeNode<T>* Add(AVLTreeNode<T>* p, T x); 

    //����������� ������� �������� ���� �� �����
    AVLTreeNode<T>* Remove(AVLTreeNode<T>* p, int k); 

public:
    
    // ������������
    AVLTree();
    AVLTree(const AVLTree<T>& tree);
    
    // �������� ������������
    AVLTree<T>& operator= (const AVLTree<T>& tree);
    
    // ����������� ������ ��������� �������
    virtual void Insert(const T& item);
    virtual void Delete(const T& item);
};

template<class T>
inline AVLTreeNode<T>* AVLTree<T>::GetAVLTreeNode(const T& item, AVLTreeNode<T>* lptr, AVLTreeNode<T>* rptr) {
    AVLTreeNode<T>* p;
    p = new AVLTreeNode<T>(item, lptr, rptr);
    if (p == NULL) {
        cerr << "������ ��������� ������!" << endl;
        exit(1);
    }
    return p;
}


//������� ����������� ������
template<class T>
inline AVLTreeNode<T>* AVLTree<T>::CopyTree(AVLTreeNode<T>* t) {
   
    AVLTreeNode<T>* newlptr, * newrptr, * newnode;
    i
        f (t == NULL)                       //���� ������ ������
        return NULL;
    
    //������� ����Tree ��������� ������� ������ �������
    if (t->Left() != NULL)
        newlptr = CopyTree(t->Left());      //���� �� ����, ��������� ��� �����
    else newlptr = NULL;
    if (t->Right() != NULL)
        newrptr = CopyTree(t->Right());
    else newrptr = NULL;

    //��������� ������ ������ ����� �����
    newnode = GetAVLTreeNode(t->data, newlptr, newrptr);
    newnode->balanceFactor = t->GetBF();    //������� ������
    return newnode;                         //������� ��������� �� ����� ��������� ������
}


//�������� ������
template <class T>
AVLTreeNode<T>* AVLTree<T>::RotateRight(AVLTreeNode<T>*& p) {
    AVLTreeNode<T>* q = p->LeftLink;        //�������� ���� = ����� ��� ��������
    p->LeftLink = (q->RightLink);           //����� ��� ������ ������ ������� ����
    q->RightLink = (p);                     //������ ������� ���� = ��������

    //������������� ������� �����
    this->FixBF(p);
    this->FixBF(q);
    return q;                               //���������� ��������� ����
}


//������ �����
template <class T>
AVLTreeNode<T>* AVLTree<T>::RotateLeft(AVLTreeNode<T>*& p) {
    AVLTreeNode<T>* q = p->RightLink;       //�������� ���� = ������ ��� ��������
    p->RightLink = (q->LeftLink);           //������ ��� ������ ����� ������� ����
    q->LeftLink = (p);                      //����� ������� ���� = ��������

    //������������� ������� �����
    this->FixBF(p);
    this->FixBF(q);
    return q;                               //���������� ��������� ����
}


//���������� ������ ����
template <class T>
int AVLTree<T>::Height(AVLTreeNode<T>* node) {
    if (node != NULL) return node->GetBF();  //���� ���� �� ������
    return 0;
}


//���������� ������� ����
template <class T>
int AVLTree<T>::BFactor(AVLTreeNode<T>* node) {

    //���������� ������ ��� ������� �����
    return this->Height(node->RightLink) - this->Height(node->LeftLink);
}


//��������� ��������� ������� ����
template <class T>
void AVLTree<T>::FixBF(AVLTreeNode<T>* node) {
    int hl = this->Height(node->LeftLink);              //������ ������ �������
    int hr = this->Height(node->RightLink);             //������ ������� �������
    node->balanceFactor = ((hl > hr ? hl : hr) + 1);    //��������� ����
}


//������� ������������ ����
template <class T>
AVLTreeNode<T>* AVLTree<T>::Balance(AVLTreeNode<T>* p) {
    this->FixBF(p);                                      //��������� ������
    
    if (this->BFactor(p) == 2) {
        if (this->BFactor(p->RightLink) < 0)
            p->RightLink = (this->RotateRight(p->RightLink));
        return this->RotateLeft(p);                      //������� �����
    }
    
    if (this->BFactor(p) == -2) {
        if (this->BFactor(p->LeftLink) > 0)
            p->LeftLink = (this->RotateLeft(p->LeftLink));
        return this->RotateRight(p);                     //������� ������
    }
    
    return p;
}


//����������� ������� ���������� ����
template <class T>
AVLTreeNode<T>* AVLTree<T>::Add(AVLTreeNode<T>* p, T x) { // ������� ����� k � ������ � ������ p
    if (!p) return GetAVLTreeNode(x, NULL, NULL);

    if (x < p->data)                                    //����� ����������� �������
        p->LeftLink = (this->Add(p->LeftLink, x));
    else
        p->RightLink = (this->Add(p->RightLink, x));

    return this->Balance(p);                            //���������� ���������������� ����
}


//����� ������������ ����
template <class T>
AVLTreeNode<T>* AVLTree<T>::FindMin(AVLTreeNode<T>* p) {
    return p->LeftLink ? this->FindMin(p->LeftLink) : p;
}


//����������� ������� �������� ���� �� �����
template <class T>
AVLTreeNode<T>* AVLTree<T>::Remove(AVLTreeNode<T>* p, int k) {
    if (!p) return 0;                                   //���� ������ �������
    
    if (k < p->data)                                    //����� ����������� ��������
        p->LeftLink = this->Remove(p->LeftLink, k);
    else if (k > p->data)
        p->RightLink = this->Remove(p->RightLink, k);
    else {
        AVLTreeNode<T>* q = p->LeftLink;
        AVLTreeNode<T>* r = p->RightLink;
        if (!r) return q;                               //���� ��� ������� ����, �� ���������� �����
        AVLTreeNode<T>* min = this->FindMin(r);         //���� ����������� ����
        min->RightLink = this->RemoveMin(r);            //������� ����������� ���� � ��������� ��� ������� �������
        min->LeftLink = q;                              //������������ ������ ������� ���������� ����
        if (p != this->root) this->FreeTreeNode(p);     //���� ��������� ���� �� ������
        else {                                          //����� �������������� ������
            this->root = min;
            this->FreeTreeNode(p);
        }
        return this->Balance(min);                      //���������� ���������������� ����� ����
    }
    return this->Balance(p);                            //���������� ���������� ����
}


//�������� ���� � ����������� ������ �� ������ p
template <class T>
AVLTreeNode<T>* AVLTree<T>::RemoveMin(AVLTreeNode<T>* p) {
    
    if (p->LeftLink == NULL)                            //���� ��� ������ �������
        return p->RightLink;                            //�� ���������� �������
    
    p->LeftLink = this->RemoveMin(p->LeftLink);         //���������� �����
    
    return this->Balance(p);                            //���������� ���������������� ����
}


//������ �����������
template<class T>
inline AVLTree<T>::AVLTree() {
    this->size = 0; this->root = NULL; this->current = NULL;
}


//����������� �����������
template<class T>
inline AVLTree<T>::AVLTree(const AVLTree<T>& tree) {
    this = tree;
}


//��������������� ������������
template<class T>
inline AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& tree) {
    if (this == &tree) return *this;
    
    this->ClearList();                                  //������� ������
    this->root = this->CopyTree((AVLTreeNode<T>*)tree.root); //�������� ������ ������
    this->current = this->root;                         //������� ��������� �� ������
    this->size = tree.size;                             //�������� ���-�� ���������
    
    return *this;                                       //����������
}


//����� �������
template<class T>
inline void AVLTree<T>::Insert(const T& item) {
    this->root = this->Add((AVLTreeNode<T>*)this->root, item);
    this->size++;       //����������� �������
}


//����� ��������
template<class T>
inline void AVLTree<T>::Delete(const T& item) {
    this->root = this->Remove((AVLTreeNode<T>*)this->root, item);
    this->size--;       //��������� �������
}


//�������������� ������ ������ �� �����
template <class T>
void PrintTreeB(AVLTreeNode<T>* t, int level) {
    if (t != NULL) {                            //���� ��������� �� ����
        PrintTree(t->Right(), level + 1);       //�������� ������ ���������
        IndentBlanks(6 * level);                //������� �������� � ������������
        cout << t->data << endl;
        PrintTree(t->Left(), level + 1);        //�������� ����� ���������
    }
}


//�������������� ������ ������ � ����
template <class T>
void PrintTreeFile(AVLTreeNode<T>* t, int level, string s1) {
    if (t != NULL) {
        ofstream f(s1, ios_base::app);
        PrintTreeFile(t->Right(), level + 1, s1); //�������� ������ ���������
        for (int i = 0; i < 6 * level; i++) {
            f << " ";
        }
        f << t->data << endl;
        PrintTreeFile(t->Left(), level + 1, s1); //�������� ����� ���������
    }
}

#endif 
