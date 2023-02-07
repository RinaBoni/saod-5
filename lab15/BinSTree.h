#pragma once

#include <iostream>
#include "TreeNode.h"

template <class T>
class BinSTree {
private:					
	// текущий элемент дерева
	TreeNode<T>* current;	
	// корень дерева
	TreeNode<T>* root;		
	//число элементов дерева
	int size;				
public:						
	
	//текущий элемент
	TreeNode<T>* getCurrent() {
		if (this->current != nullptr)
			return this->current;
		else {
			std::cerr << "Current node is empty!";
			exit(1);
		}
	}

	//размер
	int getSize()
	{
		return this->size;
	}

	//корень
	TreeNode<T>* getRoot() {
		if (this->root != nullptr)
			return this->root;
		else {
			std::cerr << "Root is empty!";
			exit(1);
		}
	}

	//распределение/освобождение памяти
	TreeNode<T>* getTreeNode(T item, TreeNode<T>* lptr = nullptr, TreeNode<T>* rptr = nullptr) {
		TreeNode<T>* p;										// объвление нового узла
		p = new TreeNode<T>(item, lptr, rptr);				// заполнение нового узла	
		if (p == nullptr)									// если узел пустой то вернуть ошибку
		{
			std::cerr << "Error while memory allocation!\n";
			exit(1);
		}													// иначе вернуть ссылку на узел узел
		return p;
	}

	// удаление узла
	void deleteTreeNode(const T& item)

	{
		TreeNode<T>* dNodePtr, * pNodePtr, * rNodePtr;
		rNodePtr = nullptr;
		dNodePtr = findNode(item, pNodePtr);
		if (dNodePtr == nullptr)
			return;

		//если нет обоих потомков
		if (dNodePtr->left == nullptr && dNodePtr->right == nullptr && pNodePtr != nullptr) {
			if (dNodePtr->data < pNodePtr->data)
				pNodePtr->left = rNodePtr;
			else
				pNodePtr->right = rNodePtr;
			freeTreeNode(dNodePtr);
			this->size--;
			return;
		}
		//если есть только левый сын
		else if (dNodePtr->right == nullptr)
			rNodePtr = dNodePtr->left;

		//если есть только правый сын
		else if (dNodePtr->left == nullptr)
			rNodePtr = dNodePtr->right;

		//если есть оба потомка
		else {
			TreeNode<T>* pOfRNodePtr = dNodePtr;
			rNodePtr = dNodePtr->left;

			while (rNodePtr->right != nullptr)
			{
				pOfRNodePtr = rNodePtr;
				rNodePtr = rNodePtr->right;
			}

			if (pOfRNodePtr == dNodePtr)
				rNodePtr->right = dNodePtr->right;

			else 
				pOfRNodePtr->right = rNodePtr->left;
		}

		// если нечем заменить то это корневой узел удаляем его
		if (rNodePtr == nullptr) {
			this->root = rNodePtr;
		}

		else if (pNodePtr != nullptr && dNodePtr->data < pNodePtr->data)
			pNodePtr->left = rNodePtr;

		else if (pNodePtr != nullptr && dNodePtr->data >= pNodePtr->data)
			pNodePtr->right = rNodePtr;

		else if(dNodePtr->data > rNodePtr->data) {
			rNodePtr->right = dNodePtr->right;
			this->root = rNodePtr;
		}

		else {
			rNodePtr->left = dNodePtr->left;
			this->root = rNodePtr;
		}

		freeTreeNode(dNodePtr);
		this->size--;
	}

	//перегрузка оператора =
	BinSTree<T>& operator = (const BinSTree<T>& rhs)
	{
		// нельзя копировать дерево в само себя
		if (this == &rhs)
			return *this;

		// очистить текущее дерево. скопировать новое дерево в текущее объект
		clearList(this->root);
		this->root = copyTree(rhs->root);
		// присвоить текущему указателю значению корня и задать размер дерева
		this->current = this->root;
		this->size = rhs->size;
		// возвратить ссылку на текущий объект
		return *this;
	}

	//очищение
	void clearList(TreeNode<T>* t) {
		if (t != nullptr)
		{
			clearList(t->left);
			clearList(t->right);
			freeTreeNode(t);
		}
	}
	
	//копирование
	TreeNode<T>* copyTree(TreeNode<T>* t) {
		TreeNode<T>* newlptr, * newrptr, * newnode;

		if (t == nullptr)
			return nullptr;

		if (t->left != nullptr)
			newlptr = copyTree(t->left);
		else
			newlptr = nullptr;

		if (t->right != nullptr)
			newrptr = copyTree(t->right);
		else
			newrptr = nullptr;
		newnode = getTreeNode(t->data, newlptr, newrptr);

		return newnode;
	}

	// вставить item в дерево поиска
	void insert(const T& item)
	{
		//t -текущий узел, parent - предыдуший узел
		TreeNode<T>* t = root, * parent = nullptr, * newNode = new TreeNode<T>(item);
		
		// закончить на пустом дереве
		while (t != nullptr)
		{
			// обновить тещущий указатель 
			parent = t;
			if (item < t->data)
				t = t->left;
			else
				t = t->right;
		}
		// если родитель пустой, то в ставить в корень
		if (parent == nullptr)
			root = newNode;
		// если item меньше родительскоог
		else if (item < parent->data)
			parent->left = newNode;
		else
			parent->right = newNode;
		current = newNode;
		size++;
	}

	//освободить узел
	void freeTreeNode(TreeNode<T>* p) {
		delete p;
	}

	//поиск узла
	TreeNode<T>* findNode(const T& item, TreeNode<T>* parent = nullptr) const {
		TreeNode<T>* t = this->root;
		parent = nullptr;

		while (t != nullptr)
		{
			if (item == t->data)
				break;
			else
			{
				parent = t;
				if (item < t->data)
					t = t->left;
				else
					t = t->right;
			}
		}
		return t;
	}

	BinSTree() {
		this->current = nullptr;
		this->size = 0;
		this->root = nullptr;
	}

	BinSTree(TreeNode<T>* root) {
		this->current = root;
		this->size = 1;
		this->root = root;
	}
	BinSTree(const T &item) {
		this->root = new TreeNode<T>(item);
		this->current = root;
		this->size = 1;
	}
};

