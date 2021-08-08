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
		bool IsAdjacent(int u, int v) const override;

		List<Pair<int, float>> GetAdjList(int u) override;
		const List<Pair<int, float>> GetAdjList(int u) const override;
		List<Pair<int, float>>& get_adjacent_by_ref(int u);			

		void AddEdge(int u, int v, float weight) override;
		void RemoveEdge(int u, int v) override;
		void makeEmpty() override;
		void PrintGraph() const;
		void ReadGraph();
		
		Pair<int, List<Pair<int, float>>>* getVertices() const { return _vertices; } 
		
		Pair<int, List<Pair<int, float >>>& getVerticByRef(int num)
		{
			return _vertices[num-1];
		} 

		void transpose(AdjacencyList* transposedGraph);

		int* BFS(int s);

	};
}