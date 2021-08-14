//summary:
//Data structure of a graph using array of lists
#include "Pair.h"
#include "List.h"
#include "Graph.h"

namespace srg {

	class AdjacencyList : public Graph {		
	private:

		Pair<int, List<Pair<int, float>>>* _vertices;

		void destroy();		

	public:

		AdjacencyList(int size = 0);
		AdjacencyList(const AdjacencyList& other);
		virtual ~AdjacencyList() { delete[] _vertices; }

		AdjacencyList& operator=(const AdjacencyList& other);

		static AdjacencyList MakeEmptyGraph(int n);
		/// <summary>
		/// get vertices u,v and tell if such ad edge exists in graph
		/// </summary>
		/// <param name="u"> source vertex </param>
		/// <param name="v"> adjacent vertex of u </param>
		/// <returns>true if edge exists, false if doesn't </returns>
		bool IsAdjacent(int u, int v) const override;
		/// <summary>
		/// get vertex and return all his adjacency list
		/// </summary>
		/// <param name="u"> vertex to get his adjacency list</param>
		/// <returns> list of adjacency list </returns>
		List<Pair<int, float>> GetAdjList(int u) override;
		/// <summary>
		/// const method
		/// gets vertex and returns all his adjacency list
		/// </summary>
		/// <param name="u"> vertex to get his adjacency list</param>
		/// <returns> const list of adjacency list </returns>
		const List<Pair<int, float>> GetAdjList(int u) const override;
		/// <summary>
		/// get vertex and return all his adjacency list by reference
		/// </summary>
		/// <param name="u"> vertex to get his adjacency list</param>
		/// <returns> list of adjacency list </returns>
		List<Pair<int, float>>& get_adjacent_by_ref(int u);			
		/// <summary>
		/// get two vertices in the adjacency list and add an edge between them
		/// </summary>
		/// <param name="u"> source vertex </param>
		/// <param name="v"> destination vertex </param>
		/// <param name="weight"> edge weight </param>
		void AddEdge(int u, int v, float weight) override;
		/// <summary>
		/// get two vertices in the adjacency list and remove an edge between them
		/// </summary>
		/// <param name="u"> source vertex </param>
		/// <param name="v"> destination vertex </param>
		void RemoveEdge(int u, int v) override;
		/// <summary>
		/// create an empty adjacency list
		/// </summary>
		void makeEmpty() override;
		/// <summary>
		/// print adjacency list
		/// </summary>
		void PrintGraph() const;
		/// <summary>
		/// get from user couples of vertices and create edge between them
		/// </summary>
		void ReadGraph();
		/// <summary>
		/// get an empty AdjacencyList
		/// return updated parameter as the transposed AdjacencyList
		/// </summary>
		/// <param name="transposedGraph">empty Adjacency List to update as the transposed source graph formation</param>
		void transpose(AdjacencyList* transposedGraph);
		/// <summary>
		/// get an int vertex from the adjacency list
		/// return array of distances from the parameter to each vertex
		/// </summary>
		/// <param name="s"> name of vertex</param>
		/// <returns>distances array by name of vertices</returns>
		int* BFS(int s);

	};
}