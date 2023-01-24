#ifndef AVLTREENODE_H
#define AVLTREENODE_H
#include "TreeNode.h"

template <class T>
class AVLTreeNode : public TreeNode<T> {
private:
    int balanceFactor; //высота узла
    AVLTreeNode<T>* LeftLink;
    AVLTreeNode<T>* RightLink;
public:
    //конструктор
    AVLTreeNode(const T& item, AVLTreeNode<T>* lptr = NULL,
        AVLTreeNode<T>* rptr = NULL, int balfac = 1);
    ~AVLTreeNode() { delete LeftLink, delete RightLink; }
    AVLTreeNode<T>* Left(void) const;
    AVLTreeNode<T>* Right(void) const;
    //метод для доступа к новому полю данных
    int GetBF(void);
    template<class > friend class AVLTree;
};


//конструктор
template<class T>
inline AVLTreeNode<T>::AVLTreeNode(const T& item, AVLTreeNode<T>* lptr, AVLTreeNode<T>* rptr, int balfac)
    : TreeNode<T>(item, (TreeNode<T>*)lptr, (TreeNode<T>*)rptr), balanceFactor(balfac) {
    LeftLink = (AVLTreeNode<T>*) this->TreeNode<T>::Left();
    RightLink = (AVLTreeNode<T>*) this->TreeNode<T>::Right();
}


//геттер левого узла
template<class T>
inline AVLTreeNode<T>* AVLTreeNode<T>::Left(void) const {
    return LeftLink;
}


//геттер правого узла
template<class T>
inline AVLTreeNode<T>* AVLTreeNode<T>::Right(void) const {
    return RightLink;
}


//геттер высоты узла
template<class T>
inline int AVLTreeNode<T>::GetBF(void) {
    return this->balanceFactor;
}
#endif 
