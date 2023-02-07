#pragma once
#include<iostream>

const int MAXSIZE = 50;
template <typename T>
class PQueue
{
	T* _pqlist;					// ������
	int _count;					// ���-�� ���������

public:

	//�����������
	PQueue(const int &size) {
		this->_pqlist = new T[size];
		this->_count = 0;
	}

	//�����������
	PQueue() {
		this->_pqlist = new T[MAXSIZE];
		this->_count = 0;
	}

	//���-�� ��������� � ������
	int lenght() const {
		return this->_count;
	}

	//�������� �� �������
	bool empty() const {
		if (this->_count == 0)
			return true;
		else
			return false;
	}

	//������� ������� �� ������� �����������
	//� ���������� ��� ��������
	T del() {
		//����� ����������� �������� � ��� ������ � ������� pqlist
		T min;
		int i, minindex = 0;		//������������ ��� pqlist[0] - ��� �������
		
		//����������� ��������� ��������
		//������� ������� � ��� ������
		if (_count > 0) {
			min = _pqlist[0];
			for(i = 1; i < _count; i++)
				if (_pqlist[i] <= min) {
					//����� ������� � �������� pqlist[i], ����� ������ - i
					min = _pqlist[i];
					minindex = i;
				}
			//����������� ��������� ������� �� ����� ������������
			//� ��������� �� ������� count
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

	//�������� ������� � ������� �����������
	void insert(const T &item) {
		//���� ��� ��� �������� ������� pqlist ������������
		//��������� ���������
		if (_count == MAXSIZE) {
			std::cerr << "Queue if full!" << std::endl;
			exit(1);
		}

		//��������� ������� � ����� ������ 
		//��������� count �� �������
		this->_pqlist[this->_count] = item;
		this->_count++;
	}

	//�������� ���� ���������
	void clear() {
		std::memset(&(this->_pqlist[0]), 0, 50);
		this->_count = 0;
	}

	//����������
	~PQueue() {
		delete[]this->_pqlist;
	}
};




