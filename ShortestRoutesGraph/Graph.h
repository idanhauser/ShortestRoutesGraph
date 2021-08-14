#pragma once
#include "List.h"
#include "Pair.h"

namespace srg {


	class Graph {							
	protected:

		int _length;						
		/// <summary>
		/// check if num is in bounds of vertices
		/// and return result as bool
		/// </summary>
		/// <param name="num">name of vertex</param>
		/// <returns>true for inbound, flase for out of bounds</returns>
		bool check_bounds(int num) const;		

	public:

		Graph(int size = 0);
		Graph(const Graph& other) = default;
		virtual ~Graph() {}

		Graph& operator=(const Graph& other) = default;
		/// <summary>
		/// returns graph amount of vertices 
		/// </summary>
		/// <returns> aomunt </returns>
		int get_length() const { return _length; }
		
		virtual bool IsAdjacent(int u, int v) const = 0;					
		
		virtual List<Pair<int, float>> GetAdjList(int u) = 0;
		
		virtual const List<Pair<int, float>> GetAdjList(int u) const = 0;
		virtual void AddEdge(int u, int v, float c) = 0;
		virtual void RemoveEdge(int u, int v) = 0;
		virtual void makeEmpty() = 0;
	};
}