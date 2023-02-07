#include <iostream>
#include "Dictionary.h"
#include "DictionaryIterator.h"
#include "KeyValue.h"
#include <fstream>
using namespace std;

//
string remove(string str, int i, int j)
{
	int k = 1;
	for (i; i <= j; i++)
	{
		if (j + k > str.length())
		{
			while (i <= j) {
				str.pop_back();
				i++;
			}
		}
		else {
			str[i] = str[j + k];
			k++;
		}
	}
	return str;
}

//распечатать объект KeyValue, содержащий ключевое слово word
void PrintEntry(const KeyValue<string, string>& word)
{
	KeyValue<string, string> w = word;
	cout << w.Key() << " - " << w.value;
}

//строка из опредедения
int ReadString(string& str, istream& istr, char delimiter = '.') {
	char tmp[256];
	int size;
	if (istr.getline(tmp, 256, delimiter)) {
		size = strlen(tmp);
		str = tmp;
		return size;
	}
	else
		return -1;

}
int main()
{
	setlocale(0, "ru");

	//входной поток данных 
	ifstream fin;
	string word, definition;
	//словарь
	Dictionary<string, string> wordDictionary("");

	//открыть файл defs.dat ключевых слов и их дефиниций
	fin.open("defs.dat", ios::in | ios::_Nocreate);
	if (!fin) {
		cerr << "Файл defs.dat не найден" << endl;
		exit(1);
	}

	//прочитать слово и его дефиницию. с помощью оператора индексирования
	//включить статью в словарь или обновить существующую дефеницию,
	//дополнив ее текущей
	while (fin >> word) {
		if (fin.eof())
			break;
		//прочитать пробел, следующий за ключевым словом
		ReadString(definition, fin);
		wordDictionary[word] += definition;
	}

	//обновить итератор дли нисходящего обхода словаря
	DictionaryIterator<string, string> dictIter(wordDictionary);

	//просматривать словарь. распечатать каждое ключевое слово
	//и его дефиницию
	cout << "Тольковый словарь:" << endl << endl;
	for (dictIter.Reset(); !dictIter.EndOfList(); dictIter.Next())
	{
		PrintEntry(dictIter.Data());
		cout << endl;
	}

	wordDictionary.clearList(wordDictionary.getRoot());
}
