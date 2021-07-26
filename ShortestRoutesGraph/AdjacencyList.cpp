#include "AdjacencyList.h"

namespace srg {


	void AdjacencyList::destroy()
	{
		delete[] _vertices;
		_vertices = nullptr;
		_length = 0;
	}


	AdjacencyList::AdjacencyList(int size) : Graph(size), _vertices(nullptr)
	{
		if (size > 0)
		{
			//already built in exception if new fails so no need to try
			_vertices = new Pair<int, List<Pair<int, float>>>[size];

			//init vertices numbers
			for (int i = 0; i < size; i++)
				_vertices[i].get_first() = i + 1;
		}
	}

	AdjacencyList::AdjacencyList(const AdjacencyList& other) : AdjacencyList(0)
	{
		*this = other;
	}

	AdjacencyList& AdjacencyList::operator=(const AdjacencyList& other)
	{
		if (this != &other)
		{
			destroy();

			if (other._length > 0)
			{
				_length = other._length;

				//already built in exception if new fails so no need to try
				_vertices = new Pair<int, List<Pair<int, float>>>[other._length];

				for (int i = 0; i < other._length; i++)
				{
					_vertices[i] = other._vertices[i];
				}
			}
		}

		return *this;
	}

	AdjacencyList AdjacencyList::MakeEmptyGraph(int n)
	{
		return AdjacencyList(n);
	}


	bool AdjacencyList::IsAdjacent(int u, int v) const
	{
		bool found = false;
		auto& adjacents = GetAdjList(u);

		for (auto itr = adjacents.begin(); itr != adjacents.end() && !found; ++itr)
			if (itr->get_first() == v)
				found = true;

		return found;
	}


	 List<Pair<int, float>> AdjacencyList::GetAdjList(int u)
	{
		// will create a new List because of return type
		return get_adjacent_by_ref(u);
	}


	const List<Pair<int, float>> AdjacencyList::GetAdjList(int u) const
	{
		if (!check_bounds(u))
			throw std::logic_error("out of bounds - ListGraph");
		else
			return _vertices[u - 1].get_second();
	}


	List<Pair<int, float>>& AdjacencyList::get_adjacent_by_ref(int u)
	{
		if (!check_bounds(u))
			throw std::logic_error("out of bounds - ListGraph");
		else
			return _vertices[u - 1].get_second();
	}


	void AdjacencyList::AddEdge(int u, int v, float weight)
	{
		if (!IsAdjacent(u, v))
			get_adjacent_by_ref(u).insert_to_tail(Pair<int, float>(v, weight));
	}


	void AdjacencyList::RemoveEdge(int u, int v)
	{
		auto& adjacents = get_adjacent_by_ref(u);

		for (auto itr = adjacents.begin(); itr != adjacents.end(); ++itr)
		{
			if (itr->get_first() == v)
			{
				itr.itr_delete();
				break;
			}
		}
	}


	void AdjacencyList::makeEmpty()
	{
		for (int i = 0; i < _length; i++)
			_vertices[i].get_second().make_empty();
	}


	void AdjacencyList::PrintGraph() const
	{
		for (int i = 0; i < _length; ++i)
			std::cout << _vertices[i].get_first() << ": " << _vertices[i].get_second() << std::endl;
	}

}