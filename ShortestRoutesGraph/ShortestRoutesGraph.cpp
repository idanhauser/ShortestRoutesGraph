// ShortestRoutesGraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "AdjacencyList.h"
using namespace srg;
using namespace std;
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
	
}

int main()
{
    int numberOfEdeges;
	int start;
	int target;
	AdjacencyList g_adjacencies;

	cin >> numberOfEdeges >> start >> target;

	g_adjacencies = AdjacencyList(numberOfEdeges);
 	

	
}
