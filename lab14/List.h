#pragma once
template <class T> 
class List	// абстрактный класс
{
protected:
	// число элементов списка, обновляемое производным классом
	int size;
public:
	//конструктор устанавливает size в 0 
	List(void) {
		size = 0;
	};

	//ввернуть размер списка 
	virtual int ListSize(void) const {
		return size;
	};

	//проверить, пуст ли список
	virtual int ListEmpty(void) const {
		return size == 0;
	};

	//найти
	virtual int Find(const T& item) = 0;

	//вставить элемент
	virtual void Insert(const T& item) = 0;

	//удалить элемент
	virtual void Delete(const T& item) = 0;

	//очистить список
	virtual void ClearList(void) = 0;
};