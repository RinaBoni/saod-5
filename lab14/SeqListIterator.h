#pragma once
#include <iostream>
#include "SeqList.h"
#include "Iterator.h"
template <class T>
class SeqListIterator : public Iterator<T> {
	SeqList<T>* listPtr;			//локальный указатель на объект SeqList
	Node<T>* prevPtr, * currPtr;	//предыдущая и текущая позиция

public:

	//конструктор
	SeqListIterator(SeqList<T>& lst) : Iterator<T>(){
		listPtr = &lst;
		this->iterationComplete = listPtr->llist.ListEmpty();
		Reset();
	}

	//продвинуться к следующему элементу списка
	virtual void Next() {
		//currPtr == nullptr, мы в конце списка
		if (currPtr == NULL)		
			return;
		//передвинуть указатель prevPtr на один узел вперед
		prevPtr = currPtr;
		//currPtr на один узел вперед
		currPtr = currPtr->NextNode();
		//если обнаружен конец связанного списка
		if (currPtr == NULL)
			this->iterationComplete = 1;	//установить флаг "итерация завершена"
	}

	//переход к началу списка
	virtual void Reset() {
		this->iterationComplete = listPtr->llist.ListEmpty();	//переприсвоить состояние итерации
		
		//вернуться если список пуст
		if (listPtr->llist.front == nullptr)
			return;
		prevPtr = nullptr;
		currPtr = listPtr->llist.front;		//установить механизмы прохождения списка с первого узла
	}

	//возвратить данные, расположенные в текущем элементе списка
	virtual T& Data() {
		if (listPtr->llist.ListEmpty() || currPtr == nullptr) {
			//если список пуст или прохождение уже 
			std::cerr << "Data: недопустимая ссылка!" << std::endl;
			//возвращаем ошибку
			exit(1);
		}
		return currPtr->data;
	}

	//сейчас итератор должен проходить список lst
	//переназначьте listPtr и вызовите reset
	void SetList(SeqList<T>& lst) {
		listPtr = &lst;
		Reset();	//инициализировать механизм прохождения для списка lst
	}
};