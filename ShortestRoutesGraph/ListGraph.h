#include "Pair.h"
#include "List.h"
#include "Graph.h"

namespace alg {

	class ListGraph : public Graph {			// graph implimented as list graph
	private:

		Pair<int, List<Pair<int, float>>>* _vertices;

		void destroy();							// deletes the graph

	public:

		ListGraph(int size = 0);
		ListGraph(const ListGraph& other);
		virtual ~ListGraph() { delete[] _vertices; }

		ListGraph& operator=(const ListGraph& other);

		static ListGraph make_empty_graph(int n);
		bool is_adjacent(int u, int v) const override;

		List<Pair<int, float>> get_adjacent(int u) override;
		const List<Pair<int, float>> get_adjacent(int u) const override;
		List<Pair<int, float>>& get_adjacent_by_ref(int u);				//for performance

		void add_edge(int u, int v, float c) override;
		void remove_edge(int u, int v) override;
		void make_empty() override;

		void print() const;
	};
}