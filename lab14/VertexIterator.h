#pragma once
#include "SeqListIterator.h"
#include "Graph.h"	

//доступ к компонентам графа
template<class T>
class VertexIterator : public SeqListIterator<T>
{
public:
	VertexIterator(Graph<T>& G) : SeqListIterator<T>(G.vertexList) {};
};
