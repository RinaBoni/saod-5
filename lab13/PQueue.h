#pragma once
#include<iostream>

const int MAXSIZE = 50;
template <typename T>
class PQueue
{
	T* _pqlist;					// массив
	int _count;					// кол-во элементов

public:

	PQueue() {
		this->_pqlist = new T[MAXSIZE];
		this->_count = 0;
	}

	int lenght() const {
		return this->_count;
	}

	bool empty() const {
		if (this->_count == 0)
			return true;
		else
			return false;
	}

	T del() {
		if (empty() == false)
		{
			T min = _pqlist[0];
			int tindex = 0;
			for (int i = 0; i < _count; i++)
			{
				if (_pqlist[i] < min) {
					min = _pqlist[i];
					tindex = i;
				}
			}
			this->_pqlist[tindex] = this->_pqlist[this->_count-1];
			_count--;
			return min;
		}
		else
			std::cerr << "Queue is empty!" << std::endl;
	}

	void insert(const T &item) {
		if (_count == MAXSIZE) {
			std::cerr << "Queue if full!" << std::endl;
			exit(1);
		}
		this->_pqlist[this->_count] = item;
		this->_count++;
	}

	void clear() {
		std::memset(&(this->_pqlist[0]), 0, 50);
		this->_count = 0;
	}

	~PQueue() {
		delete[]this->_pqlist;
	}
};

