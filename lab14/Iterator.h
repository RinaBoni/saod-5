#pragma once

template<class T>
class Iterator
{
protected:
	//флаг, показывающий, достиг ли итератор концв списка
	//должен поддерживаться производными классами
	int iterationComplete;
public:
	//конструктор
	Iterator() : iterationComplete{ 0 }
	{}
	//обязательные методы итератора
	virtual void Next() = 0;
	virtual void Reset() = 0;

	//методы выборки/модификации данных
	virtual T& Data() = 0;

	//проверка конца списка
	virtual int EndOfList() const {
		return iterationComplete;
	}
};
