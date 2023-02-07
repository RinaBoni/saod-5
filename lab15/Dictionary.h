#pragma once
#include "BinSTree.h"
#include "KeyValue.h"

template <class K, class T>
class Dictionary : public BinSTree<KeyValue<K,T>>
{
private:
	//��������, ������������� �������� ������� �� ���������
	//������������ ���������� ��������������, � ����� ��������
	//InDictionary � DeleteKey
	T defaultValue;

public:
	//�����������
	Dictionary(const T& defaultval) : BinSTree < KeyValue<K, T>>(), defaultValue(defaultval) {};
	
	//�������� ��������������
	T& operator[] (const K& index);

	///////////////�������������� ��������� ������//////////////
	//��������� ������� � ������� ���� ����-�������� � ������ keyval
	int InDictionary(const K& keyval);
	//������� ��������� ������, ������� ���� keyval
	void DeleteKey(const K& keyval);
};


//�������� ��������������. ����� �������� ����� ��� ������
template <class K, class T>
T& Dictionary<K, T>::operator[] (const K& index) {
	//���������� ������� ������ ���� KeyValue, ����������
	//������ ���������� �� ���������
	KeyValue<K, T> targetKey(index, defaultValue);

	//������ ����. ���� ������, �������� targetKey
	if (!this->findNode(targetKey))
		this->insert(targetKey);
	//���������� ������ �� ��������� � ���������� ������
	return this->getCurrent()->data.value;
}


//��������� ���������� �� ������ ���� KeyValue
//� ������ ������
template <class K, class T>
int Dictionary<K, T>::InDictionary(const K& keyval) {
	//���������� ������� ������ ���� KeyValue, ����������
	//������ ���������� �� ���������
	KeyValue<K, T> tmp(keyval, defaultValue);
	
	//������ tmp �� ������. ������� ���������
	return !this->findNode(tmp);
}


//������� ������ ���� KeyValue � ������ ������ �� �������
template <class K, class T>
void Dictionary<K, T>::DeleteKey(const K& keyval) {
	KeyValue<K, T> tmp(keyval, defaultValue);
	this->deleteTreeNode(tmp);
}