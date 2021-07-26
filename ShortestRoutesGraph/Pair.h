#pragma once
#include <iostream>

namespace srg {

	template<typename first, typename second>
	class Pair {								// really simple template class to hold 2 variables together
	private:

		first _first;
		second _second;

	public:

		Pair() : _first(), _second() {}
		Pair(const first& f, const second& s) : _first(f), _second(s) {}
		Pair(const Pair& other) : Pair(other._first, other._second) {}
		~Pair() { return; }

		Pair& operator=(const Pair& other)
		{
			_first = other._first;
			_second = other._second;

			return *this;
		}

		first& get_first() { return _first; }
		const first& get_first() const { return _first; }
		void set_first(const first& new_first) { _first = new_first; }

		second& get_second() { return _second; }
		const second& get_second() const { return _second; }
		void set_second(const second& new_second) { _second = new_second; }

		friend std::ostream& operator<<(std::ostream& os, const Pair& p)
		{
			return os << "{ " << p._first << ", " << p._second << " }";
		}
	};
}