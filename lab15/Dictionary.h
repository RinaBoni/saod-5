#pragma once
#include "BinSTree.h"
#include "KeyValue.h"

template <class K, class T>
class Dictionary : public BinSTree<KeyValue<K,T>>
{
private:
	//значение, присваиваемое эдементу словаря по умолчанию
	//используется оператором индеусирования, а также методами
	//InDictionary и DeleteKey
	T defaultValue;

public:
	//конструктор
	Dictionary(const T& defaultval) : BinSTree < KeyValue<K, T>>(), defaultValue(defaultval) {};
	
	//оператор индексирования
	T& operator[] (const K& index);

	///////////////дополнительные словарные методы//////////////
	//проверяет наличие в словаре пары ключ-значение с ключем keyval
	int InDictionary(const K& keyval);
	//удаляет словарную статью, имеющую ключ keyval
	void DeleteKey(const K& keyval);
};


//оператор индексированию. здесь делается почти вся работа
template <class K, class T>
T& Dictionary<K, T>::operator[] (const K& index) {
	//определить целевой объект типа KeyValue, содержащий
	//данные задаваемые по умолчанию
	KeyValue<K, T> targetKey(index, defaultValue);

	//искать ключ. если найден, вставить targetKey
	if (!this->findNode(targetKey))
		this->insert(targetKey);
	//возвратить ссылку на найденные и всталенные данные
	return this->getCurrent()->data.value;
}


//проверить существует ли объект типа KeyValue
//с данным ключем
template <class K, class T>
int Dictionary<K, T>::InDictionary(const K& keyval) {
	//определить целевой объект типа KeyValue, содержащий
	//данные задаваемые по умолчанию
	KeyValue<K, T> tmp(keyval, defaultValue);
	
	//искать tmp на дереве. вернуть результат
	return !this->findNode(tmp);
}


//удалить объект типа KeyValue с данным ключем из словаря
template <class K, class T>
void Dictionary<K, T>::DeleteKey(const K& keyval) {
	KeyValue<K, T> tmp(keyval, defaultValue);
	this->deleteTreeNode(tmp);
}