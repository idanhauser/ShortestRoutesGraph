#include "Pair.h"
#include "List.h"
#include "Graph.h"

namespace srg {

	class AdjacencyList : public Graph {			// graph implimented as list graph
	private:

		Pair<int, List<Pair<int, float>>>* _vertices;

		void destroy();							// deletes the graph

	public:

		AdjacencyList(int size = 0);
		AdjacencyList(const AdjacencyList& other);
		virtual ~AdjacencyList() { delete[] _vertices; }

		AdjacencyList& operator=(const AdjacencyList& other);

		static AdjacencyList MakeEmptyGraph(int n);
		bool IsAdjacent(int u, int v) const override;

		List<Pair<int, float>> GetAdjList(int u) override;
		const List<Pair<int, float>> GetAdjList(int u) const override;
		List<Pair<int, float>>& get_adjacent_by_ref(int u);				//for performance

		void AddEdge(int u, int v, float weight) override;
		void RemoveEdge(int u, int v) override;
		void makeEmpty() override;

		void PrintGraph() const;
	};
}