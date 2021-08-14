#include "Graph.h"

namespace srg {
	/// <summary>
/// check if num is in bounds of vertices
/// and return result as bool
/// </summary>
/// <param name="num">name of vertex</param>
/// <returns>true for inbound, flase for out of bounds</returns>
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