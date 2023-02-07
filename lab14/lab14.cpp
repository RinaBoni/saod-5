#include <iostream>
#include "Graph.h"
#include "VertexIterator.h"

using namespace std;


template <class T>
void Warshall(Graph<T>& G) {
    VertexIterator<T> vi(G), vj(G);
    int i, j, k;
    int WSM[MAXGRAPHSIZE][MAXGRAPHSIZE];
    int n = G.NumberOfVertices();

    for (vi.Reset(), i = 0; !vi.EndOfList(); vi.Next(), i++)
        for (vj.Reset(), j = 0; !vj.EndOfList(); vj.Next(), j++)
            if (i == j)
                WSM[i][i] = 1;
            else
                WSM[i][j] = G.GetWeight(vi.Data(), vj.Data());
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            for (k = 0; k < n; k++)
                WSM[i][j] != WSM[i][k] && WSM[k][j];

    for (vi.Reset(), i = 0; !vi.EndOfList(); vi.Next(), i++) {

        cout << vi.Data() << ": ";
        for (j = 0; j < n; j++)
            cout << WSM[i][j] << " ";
        cout << endl;
    }
}



int main()
{
	setlocale(0, "ru");

	/*********лаб 13.6*********/

    Graph<string> G;

	G.InsertVertex("Solt-Lake city");
	G.InsertVertex("Albuquerque");
	G.InsertVertex("Phoenix");
	G.InsertVertex("San-Diego");
    G.InsertVertex("San-Francisco");
	G.InsertEdge("Solt-Lake city", "Albuquerque", 604);
	G.InsertEdge("Solt-Lake city", "Phoenix", 648);
	G.InsertEdge("Solt-Lake city", "San-Francisco", 752);
	G.InsertEdge("San-Francisco", "Phoenix", 763);
	G.InsertEdge("San-Francisco", "San-Diego", 504);
	G.InsertEdge("San-Diego", "Phoenix", 763);
    G.InsertEdge("Phoenix", "Albuquerque", 432);

	string S;
	
    cout << "Задача 13.6" << endl;
    cout <<  endl;

    cout << "Вывать мин. расстояние при оправлении из: ";
	cin >> S;

    cout << endl;
	VertexIterator<string> viter(G);
	for (viter.Reset(); !viter.EndOfList(); viter.Next()) {
		cout << "Минимальное расстояние от аэропорта " << S <<
			" до аэропорта " << viter.Data() << " = "
			<< G.MinimumPath(S, viter.Data()) << endl;
	}

    /*********лаб 13.7*********/

    Graph<char>Gg;
    Gg.InsertVertex('A');
    Gg.InsertVertex('B');
    Gg.InsertVertex('C');
    Gg.InsertVertex('D');
    Gg.InsertVertex('E');
    Gg.InsertEdge('A', 'B', 1);
    Gg.InsertEdge('A', 'C', 1);
    Gg.InsertEdge('E', 'D', 1);

    cout << endl;
    cout << endl;
    cout << "Задача 13.7" << endl;
    cout << endl;

    cout << "Матрица достижимости:" << endl;
    Warshall(Gg);
}

