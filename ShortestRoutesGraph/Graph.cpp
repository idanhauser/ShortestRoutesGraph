#include "Graph.h"

namespace srg {

	bool Graph::check_bounds(int num) const
	{
		return num > 0 && num <= _length;
	}


	Graph::Graph(int size) : _length(0)
	{
		if (size < 0)
			throw std::logic_error("Tried initializing a graph with a negative number");
		else if (size > 0)
			_length = size;
	}

}