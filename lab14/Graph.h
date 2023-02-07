#pragma once
#include "SeqList.h"
#include "SeqListIterator.h"
#include <stack>
#include "PQueue.h"
const int MAXGRAPHSIZE = 25;

template<class T>
class VertexIterator;
template<class T>
class Graph
{

private:
	SeqList<T> vertexList;
	int edge[MAXGRAPHSIZE][MAXGRAPHSIZE];
	int graphsize;
	int FindVertex(SeqList<T>& L, const T& vertex);
	int GetVertexPos(const T& vertex);

public:
	// конструктор
	Graph();

	// методы тестирования графа
	int GraphEmpty() const;
	int GraphFull() const;

	// методы обработки данных
	int NumberOfVertices() const;
	int NumberOfEdges() const;
	int GetWeight(const T& vertex1, const T& vertex2);
	SeqList<T>& GetNeighbors(const T& vertex);

	// методы модифицкации графа
	void InsertVertex(const T& vertex);
	void InsertEdge(const T& vertex1, const T& vertex2,const int &weight);
	void DeleteVertex(const T& vertex);
	void DeleteEdge(const T& vertex1, const T& vertex2);

	// утилиты
	void ReadGraph(const char* filename);
	int MinimumPath(const T& sVertex, const T& eVertex);
	SeqList<T>& DepthFirstSerch(const T& beginVertex);
	SeqList<T>& BreadthFirstSearch(const T& beginVertex);

	// итератор для обхода вершин
	friend class VertexIterator<T>;
};

//проверяет наличие вершины в списке L и исп в поисковых методах
template<class T>
int Graph<T>::FindVertex(SeqList<T>& L, const T& vertex) {
	return L.Find(vertex);
}

// конструктор. обнуляет матрицу смежности и переменную graphsize
template<class T>
Graph<T>::Graph() : vertexList() {
	for (int i = 0; i < MAXGRAPHSIZE; i++)
		for (int j = 0; j < MAXGRAPHSIZE; j++)
			edge[i][j] = 0;
	graphsize = 0;
}

//сканирование списка вершин и возвращение позиции вершины в этом списке
template<class T>
int Graph<T>::GetVertexPos(const T& vertex) {
	SeqListIterator<T> liter(vertexList);
	int pos = 0;
	while (!liter.EndOfList() && liter.Data() != vertex) {
		pos++;
		liter.Next();
	}
	return pos;
}


//возвращает вес ребра, которое соединяет vertex1 и vertex2
template<class T>
int Graph<T>::GetWeight(const T& vertex1, const T& vertex2) {
	int i = GetVertexPos(vertex1);
	int j = GetVertexPos(vertex2);
		if (edge[i][j] > 0)
		return edge[i][j];
	else 
		return 0;
}


//возвращает список смежных вершин
template<class T>
SeqList<T>& Graph<T>::GetNeighbors(const T& vertex) {
	SeqList<T>* L;
	SeqListIterator<T> viter(vertexList);

	//создать пустой список
	L = new SeqList<T>;

	//позиция в списке, соответствующая номеру строки матрицы смежности
	int pos = GetVertexPos(vertex);
	
	//если такой вершины vertex нет в списке вершин, закончить работу программы
	if (pos == -1) {
		cerr << "GetNeighbors: такой вершины нет в графе." << endl;
		return *L;
	}
	
	//сканироватт строку матрицы смежности и включить в список 
	//все вершины, имеющие ребро ненулевого веса из vertex
	for (int i = 0; i < graphsize; i++) {
		if (edge[pos][i] > 0)
			L->Insert(viter.Data());
		viter.Next();
	}
	return *L;
}


//удалить вершину из списка вершин и скорректировать матрицу смежности,
//удалив принадлежащие этой вершине ребра
template<class T>
void Graph<T>::DeleteVertex(const T& vertex) {
	//получить позицию вершины в списке вершин
	int pos = GetVertexPos(vertex);
	int row, col;

	//если такой вершины нет, сообщить об этом и вернуть управление
	if (pos == -1) {
		cerr << "DeleteVertex: у вершиные нет графы" << endl;
		return;
	}

	//удалить вершину и уменьшить graphsize 
	vertexList.Delete(vertex);
	graphsize--;
	
	//матрица смежности делится на три области
	for (row = 0; row < pos; row++)						//область I
		for (col = pos + 1; col < graphsize; col++)
			edge[row][col - 1] = edge[row][col];

	for (row = pos+1; row < graphsize; row++)			//область II
		for (col = pos + 1; col < graphsize; col++)
			edge[row-1][col - 1] = edge[row][col];

	for (row = pos+1; row < graphsize; row++)			//область III
		for (col = 0; col < pos; col++)
			edge[row-1][col] = edge[row][col];
}


//начиная с начальной вершины, сформировать список вершин,
//обрабатываемых в порядке обхода "сначала в глубину"
template <class T>
SeqList<T>& Graph<T>::DepthFirstSerch(const T& beginVertex) {
	//стек для временного хранения вершин, ожидающих обработки
	stack<T> S;

	//L - список пройденных вершин. adjL содержит вершины,
	//смежные с текущей. L создается динамически, поэтому можно
	//поэтому можно возвратить его адрес
	SeqList<T>* L, adjL;
	SeqListIterator<T> iteradjL(adjL);
	T vertex;

	//инициализировать выходной список
	//поместить начальную вершину в стек
	L = new SeqList<T>;
	S.push(beginVertex);

	//продолжить сканирование, пока не опустеет стек
	while (!S.empty()) {
		//вытолкнуть очетедную вершину 
		vertex = S.top();
        S.pop();

		//проверить ее наличие в списке L
		if (!FindVertex(*L, vertex)) {
			//если ее нет, включить вершину в L
			//а также получить все смежные с ней вершины
			(*L).Insert(vertex);
			adjL = GetNeighbors(vertex);

			//установить итератор на текуший adjL
			iteradjL.SetList(adjL);

			//сканировать список смежных вершин 
			//помещать в стек те из них, которые отсутствуют в списке L
			for (iteradjL.Reset(); !iteradjL.EndOfList(); iteradjL.Next())
				if (!FindVertex(*L, iteradjL.Data()))
					S.push(iteradjL.Data());
		}
	}
	//возвратить выходной список
	return *L;
}

//объекты типа PathInfo описывают путь, существующий между 
//двумя вершинами и его стоимость
template<class T>
struct PathInfo
{
	T startV, endV;
	int cost;
};

//перегрузка оператора<=
template<class T>
int operator <= (const PathInfo<T>& a, const PathInfo<T> b)
{
	return a.cost <= b.cost;
}

//минимальный путь
template <class T>
int Graph<T>::MinimumPath(const T& sVertex, const T& eVertex) {
	//очередь приоритетов, в которую помещаются объекты,
	//несущие информацию о стоимости путей из sVertex
	PQueue<PathInfo<T>> PQ(MAXGRAPHSIZE);

	//используется при вставке/удалении объектов PathInfo в очереди приоритетов
	PathInfo<T> pathData;

	//L - список всех вершин, достижимых из sVertex и стоимость которых уже учтена
	//adjL - список вершин, смежных с посещаемой на данный момент
	//для сканирование adjL использутся итератор adjLiter
	SeqList<T> L, adjL;
	SeqListIterator<T> adjLiter(adjL);
	T sv, ev;
	int mincost;

	//сформировать начальный элемент очереди приоритетов
	pathData.startV = sVertex;
	pathData.endV = sVertex;

	//стоимость пути из sVertex в eVertex равна 0
	pathData.cost = 0;
	PQ.insert(pathData);

	//обрабатывать вершины, пока не будет найден минимальный путь к eVertex
	//или пока не опустеет очередь приоритетов
	while (!PQ.empty()) {
		//удалить элемент приоритетной очереди и запомнить 
		//его конечную вершину и стоимость от sVertex
		pathData = PQ.del();
		ev = pathData.endV;
		mincost = pathData.cost;

		//если это eVertex
		//то минимальный путь от sVertex к eVertex найден
		if (ev == eVertex)
			break;

		//если конечная вершина уже имеется в L,
		//не рассматривать ее снова
		if (!FindVertex(L, ev)) {
			L.Insert(ev);
			
			//найти все смежные с ev вершины. для тех из них,
			//которых нет в L, сформировать объекты PathInfo с начальными 
			//вершинами, равнными ev, и включить их в очередь приоритетов
			sv = ev;
			adjL = GetNeighbors(sv);

			//новый список adjL сканируется итератором adjLiter
			adjLiter.SetList(adjL);
			for (adjLiter.Reset(); !adjLiter.EndOfList(); adjLiter.Next()) {
				ev = adjLiter.Data();
				if (!FindVertex(L, ev)) {
					//создать новый элемент приоритетной очереди
					pathData.startV = sv;
					pathData.endV = ev;
					
					//стоимость равна текущей минимальной стоимости
					//плюс стоимость от перехода от sv к ev
					pathData.cost = mincost + GetWeight(sv, ev);
					PQ.insert(pathData);
				}
			}
		}
	}
	if (ev == eVertex)
		return mincost;
	else
		return -1;
}

//граф пуст
template<class T>
int Graph<T>::GraphEmpty() const {
	return graphsize == 0;
}

//граф забит
template<class T>
int Graph<T>::GraphFull() const {
	return graphsize == MAXGRAPHSIZE;
}

//обращение к graphsize
template<class T>
int Graph<T>::NumberOfVertices() const {
	return graphsize;
}

//кол-во ребер
template<class T>
int Graph<T>::NumberOfEdges() const {
	int numOfEdges = 0;
	for (int i = 0; i < MAXGRAPHSIZE; i++)
		for (int j = i; j < MAXGRAPHSIZE; j++)
			if (edge[i][j] > 0)
				numOfEdges++;
	return numOfEdges;
}

//вставить новую вершину в множество вершин
template<class T>
void Graph<T>::InsertVertex(const T& vertex) {
	vertexList.Insert(vertex);
	graphsize++;
}

//вставить ребро (vertex1, vertex2) с весом weight в множество ребер
template<class T>
void Graph<T>::InsertEdge(const T& vertex1, const T& vertex2,const int& weight) {
	if (vertex1 != vertex2) {
		int i = GetVertexPos(vertex1);
		int j = GetVertexPos(vertex2);
		edge[i][j] = weight;
		edge[j][i] = weight;
	}
	else {
		cerr << "Not good!";
		exit(1);
	}
}

//если ребро (vertex1, vertex2) существует, удалить его из множества ребер
template <class T>
void Graph<T>::DeleteEdge(const T& vertex1, const T& vertex2) {
	if (vertex1 != nullptr && vertex2 != nullptr && vertexList.Find(vertex1) && vertexList.Find(vertex2))
	{
		int i = GetVertexPos(vertex1);
		int j = GetVertexPos(vertex2);
		edge[i][j] = 0;
	}
}

//параметр - имя файла с входным описанием вершин и ребер графа
template <class T>
void Graph<T>::ReadGraph(const char* filename) {
}


template <class T>
SeqList<T>& Graph<T>::BreadthFirstSearch(const T& beginVertex) {

}