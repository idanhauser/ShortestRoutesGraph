// Roee habiri tamir.
//  Idan hasuer 
//summary:
//the program creates an adjacency list graph, using the data the user inputs,
// and finds the shortest routes in a graph from the input of vertex s to the input of vertex t

//gets: total amount of vertices
//		vertex s
//		vertex t
//		couples of vertices to create edges

//returns: the shortest routes in the input graph from vertex s to vertex t


#include <chrono>
#include <iomanip>
#include <iostream>
#include "AdjacencyList.h"
using namespace srg;
using namespace std;


/*Instructions :
1)Enter number of vertexs.
2)Enter vertexs: S and T.
3)enter the rest of the vertesxs
4)in order to finish enter ctrl + Z
5)enter

and you will geet as an output the path of the new graph
and the runtime of the algo.
*/
int main()
{
	//getting the number of edges and S and T
    int numberOfEdeges;
	int s;
	int t;
	cin >> numberOfEdeges >> s >> t;
	if (((1 > s)  || (numberOfEdeges < s)) ||
		((1 > t) || (numberOfEdeges < t)) ||
		(numberOfEdeges<1)) {
		cout << "invalid input";
		exit(1);
	}
	
	AdjacencyList g_adjacencies;

	
	//buliding empty graph woth ctor
	g_adjacencies = AdjacencyList(numberOfEdeges);
	//reading rhe grpah
	g_adjacencies.ReadGraph();

	auto start = chrono::high_resolution_clock::now();
	// unsync the I/O of C and C++.
	ios_base::sync_with_stdio(false);
	
 	//1.run bfs on G from s
	int* d = g_adjacencies.BFS(s);

	if (d[t-1] == -1)
	{
		cout << "Given source and destination"
			<< " are not connected";
		return 0;
	}
	//2.if !(d[v] = d[u] + 1) ===>>>  delete edge (u,v) 
	for (int u = 1; u <= g_adjacencies.get_length(); u++)
	{
		auto adjacents = g_adjacencies.GetAdjList(u);
		for (auto j = adjacents.begin();	j != adjacents.end(); ++j)
		{
			int v = j->get_first();
				if (d[v - 1] != d[u - 1] + 1)
				{
					g_adjacencies.RemoveEdge(u, v);
				}
		}
	}
 	//3.build G transpose
	AdjacencyList GTranspose(g_adjacencies.get_length());
	g_adjacencies.transpose(&GTranspose);
	
	
	//4.run bfs on G transpose when the source vertice is t. delete every edge u cant get to from t.

	d = GTranspose.BFS(t);

	for (int u = 1; u <= GTranspose.get_length(); u++)
	{
		auto adjacents = GTranspose.GetAdjList(u);

		for (auto j = adjacents.begin(); j != adjacents.end(); ++j)
		{
			int v = j->get_first();
			if (d[v-1] != d[u-1] + 1)
			{
				GTranspose.RemoveEdge(u, v);
			}
		}
	}
	//graph result is called H transpose
	//build from H transpose graph H
	AdjacencyList graph_H(GTranspose.get_length());
	GTranspose.transpose(&graph_H);
	
	graph_H.PrintGraph();


	auto end = chrono::high_resolution_clock::now();
	// Calculating total time taken by the program.
	double time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	cout << "Time taken by function <name-of-fun> is : " << fixed
		<< time_taken << setprecision(9);
	cout << " sec" << endl;


 	
}

