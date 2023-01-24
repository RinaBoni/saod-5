#include <iostream>
#include "Graph.h"
#include "VertexIterator.h"

//проверяет существование направленного пути от вершины v к вершине w и возвращает тру или фолс
template <class T>
int PathConnect(Graph<T>& G, T v, T w) {
    SeqList<T> L;

    //найти вершины, связанные с v
    L = G.DepthFirstSerch(v);

    //если w в их числе нет, вернуть тру
    if (L.Find(w))
        return 1;
    else
        return 0;
}


//печать сильной компоненты
template <class T>
void PrintList(SeqList<T> &list) {
    SeqListIterator<T> liter(list);
    for (liter.Reset(); !liter.EndOfList(); liter.Next()) {
        cout << liter.Data() << " ";
    }
}

template <class T>
void ConnectedComponent(Graph<T>& G) {
    VertexIterator<T> viter(G);
    SeqList<T> markedList, scList, L, R;
    for (viter.Reset(); !viter.EndOfList(); viter.Next()) {
        //проверять в цикле каждую вершину viter.Data()
        //если не помечен, включить в сильную компоненту
        if (!markedList.Find(viter.Data())) {
            scList.ClearList();

            //получить вершины, достижимые из viter.Data()
            L = G.DepthFirstSerch(viter.Data());
            
            //искать в списке вершины, из котрых достижима вершина viter.Data()
            SeqListIterator<T> liter(L);
            for(liter.Reset(); !liter.EndOfList(); liter.Next())
                if (PathConnect(G, liter.Data(), viter.Data())) {
                    //вставить вершины в текущую сильную компоненту и в markedList
                    scList.Insert(liter.Data());
                    markedList.Insert(liter.Data());
                }
            PrintList(scList);      //печать сильной компоненты
            cout << endl;
        }
    }
    
}

int main()
{
    setlocale(0, "ru");
    Graph<const char*> G;
    G.InsertVertex("A");
    G.InsertVertex("B");
    G.InsertVertex("C");
    G.InsertVertex("D");
    G.InsertEdge("A", "B", 100);
    G.InsertEdge("A", "C", 300);
    G.InsertEdge("B", "C", 50);
    G.InsertEdge("B", "D", 10);
    G.InsertEdge("C", "D", 30);
    cout << "Сильные компоненты:" << endl;
    ConnectedComponent(G);
}
