#pragma once

template<class T>
class BinSTree;
// ќбъ€вление объекта дл€ узла бинарного дерева
template <class T> 
class TreeNode {

private:
	// укзатели левого и правого дочерних узлов
	TreeNode<T>* left;
	TreeNode<T>* right;
public:
	// открытый элемент, допускающий обновление
	T data;


	// конструктор
	TreeNode(const T& item, TreeNode<T>* lptr = nullptr, TreeNode<T>* rptr = nullptr) {
		this->data = item;
		this->left = lptr;
		this->right = rptr;
	}

	//вернуть правый
	TreeNode<T>* Right() const {							
		return this->right;
	}


	//вернуть левый
	TreeNode<T>* Left() const {								
		return this->left;
	}


	friend class BinSTree<T>;
};

