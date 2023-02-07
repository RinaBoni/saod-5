#pragma once
template <class K, class T>
class KeyValue
{
protected:
	K key;

public:
	// словарные данные €вл€ютс€ общедоступными
	T value;
	KeyValue(K keyValue, T dataValue);
	KeyValue() {
	}
	// операторы присваивани€. не измен€ют ключ
	KeyValue<K, T>& operator= (const KeyValue<K, T>& rhs);

	// операторы сравнени€. сравнивают два ключа
	int operator== (const KeyValue<K, T>& value) const;
	int operator== (const K& keyval) const;
	int operator< (const KeyValue<K, T>& value) const;
	int operator< (const K& keyval) const;

	// метод доступа к ключу
	K Key() const;
};

template <class K, class T>
KeyValue<K, T>::KeyValue(K keyValue, T datavalue) : key(keyValue), value(datavalue) {};

template <class K, class T>
KeyValue<K, T>& KeyValue<K, T>::operator= (const KeyValue<K, T>& rhs) {
	if (key != rhs.key) {
		key = rhs.key;
		value = rhs.value;
		return *this;
	}
	else return *this;
}

template <class K, class T>
int KeyValue<K, T>::operator== (const KeyValue<K, T>& value) const {
	return this->key == value.key;
}
template <class K, class T>
int KeyValue<K, T>::operator== (const K& keyval) const {
	return this->key == keyval;
}
template <class K, class T>
int KeyValue<K, T>::operator< (const KeyValue<K, T>&value) const {
	return this->key < value.key;
}
template <class K, class T>
int KeyValue<K, T>::operator< (const K& keyval) const {
	return this->key < keyval;
}
template <class K, class T>
K KeyValue<K, T>::Key() const {
	return key;
}