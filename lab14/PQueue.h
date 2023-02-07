#pragma once
#include<iostream>

const int MAXSIZE = 50;
template <typename T>
class PQueue
{
	T* _pqlist;					// массив
	int _count;					// кол-во элементов

public:

	//конструктор
	PQueue(const int &size) {
		this->_pqlist = new T[size];
		this->_count = 0;
	}

	//конструктор
	PQueue() {
		this->_pqlist = new T[MAXSIZE];
		this->_count = 0;
	}

	//кол-во элементов в списке
	int lenght() const {
		return this->_count;
	}

	//проверка на пустоту
	bool empty() const {
		if (this->_count == 0)
			return true;
		else
			return false;
	}

	//удаляет элемент из очереди приоритетов
	//и возвращает его значение
	T del() {
		//найти минимальное значение и его индекс в массиве pqlist
		T min;
		int i, minindex = 0;		//предпологаем что pqlist[0] - это минимум
		
		//просмотреть остальные элементы
		//измеряя минимум и его индекс
		if (_count > 0) {
			min = _pqlist[0];
			for(i = 1; i < _count; i++)
				if (_pqlist[i] <= min) {
					//новый минимум в элементе pqlist[i], новый индекс - i
					min = _pqlist[i];
					minindex = i;
				}
			//переместить хвостовой элемент на место минимального
			//и уменьшить на единицу count
			_pqlist[minindex] = _pqlist[_count - 1];
			_count--;
		}
		else
		{
			cerr << "Queue if empty!";
			exit(1);
		}
		return min;
	}

	//вставить элемент в очередь приоритетов
	void insert(const T &item) {
		//если уже все элементы массива pqlist использованы
		//завершить программу
		if (_count == MAXSIZE) {
			std::cerr << "Queue if full!" << std::endl;
			exit(1);
		}

		//поместить элемент в конец списка 
		//увеличить count на единицу
		this->_pqlist[this->_count] = item;
		this->_count++;
	}

	//удаление всех элементов
	void clear() {
		std::memset(&(this->_pqlist[0]), 0, 50);
		this->_count = 0;
	}

	//деструктор
	~PQueue() {
		delete[]this->_pqlist;
	}
};




