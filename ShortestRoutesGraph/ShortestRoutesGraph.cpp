// ShortestRoutesGraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "AdjacencyList.h"
using namespace srg;
using namespace std;
 /*moved to adjacencyList.cpp due to instructions
  void ReadGraph(AdjacencyList& g)
{
	 int v, u;
	 int input;
	 int weight = 0;
	 cin >> input;
	 while (input!=-1)
	 {
		 v = input;
		 cin >> u;
		 g.AddEdge(v, u, weight);
		 cin >> input;
	 }
	
}*/




int main()
{
    int numberOfEdeges;
	int start;
	int target;
	AdjacencyList g_adjacencies;

	cin >> numberOfEdeges >> start >> target;

	g_adjacencies = AdjacencyList(numberOfEdeges);

	g_adjacencies.ReadGraph();

 	//Pair<int, List<Pair<int, float>>> s = g_adjacencies.getVerticByRef(start);

 	//1.run bfs on G from s

	int* d = g_adjacencies.BFS(start);

	if (d[target-1] == -1)
	{
		cout << "Given source and destination"
			<< " are not connected";
		return 0;
	}
	//2.if !(d[v] = d[u] + 1) ===>>>  delete edge (u,v) 
	for (int u = 1; u <= g_adjacencies.get_length(); u++)
	{
		auto adjacents = g_adjacencies.GetAdjList(u);
		//todo - fix: after deleting last edge/adjacent from list, j continues to next one (making an error)
		for (auto j = adjacents.begin();	j != adjacents.end(); ++j)
		{
			int v = j->get_first();
			//if (g_adjacencies.IsAdjacent(u, v)) {
				if (d[v - 1] != d[g_adjacencies.getVerticByRef(u).get_first() - 1] + 1)
				{
					g_adjacencies.RemoveEdge(u, v);
				}
			//}
		}
	}
 	//3.build G transpose
	AdjacencyList GTranspose(g_adjacencies.get_length());
	g_adjacencies.transpose(&GTranspose);
	
	
	//4.run bfs on G transpose when the source vertice is t. delete every edge u cant get to from t.
	////todo
	//Pair<int, List<Pair<int, float>>> t = g_adjacencies.getVerticByRef(target);

	d = GTranspose.BFS(target);

	for (int u = 1; u <= GTranspose.get_length(); u++)
	{
		auto adjacents = g_adjacencies.GetAdjList(u);

		for (auto j = adjacents.begin(); j != adjacents.end(); ++j)
		{
			int v = j->get_first();
			if (d[v] != d[GTranspose.getVertices()[u].get_first()] + 1)
			{
				GTranspose.RemoveEdge(u, v);
			}
		}
	}
	//graph result is called H transpose
	//build from H transpose graph H
	////todo
	AdjacencyList graph_H(GTranspose.get_length());
	GTranspose.transpose(&graph_H);
	
	



 	
}

