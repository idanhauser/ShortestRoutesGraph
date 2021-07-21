#pragma once
#include "List.h"
#include "Pair.h"

namespace alg {


	class Graph {								// abstract class, has some basic stuff all graphs need to have
	protected:

		int _length;							// amount of vertices in the graph

		bool check_bounds(int num) const;		// check if vertex is in the allowed range

	public:

		Graph(int size = 0);
		Graph(const Graph& other) = default;
		virtual ~Graph() {}

		Graph& operator=(const Graph& other) = default;

		int get_length() const { return _length; }

		virtual bool is_adjacent(int u, int v) const = 0;					// functions every graph needs to impliment
		virtual List<Pair<int, float>> get_adjacent(int u) = 0;
		virtual const List<Pair<int, float>> get_adjacent(int u) const = 0;
		virtual void add_edge(int u, int v, float c) = 0;
		virtual void remove_edge(int u, int v) = 0;
		virtual void make_empty() = 0;
	};
}