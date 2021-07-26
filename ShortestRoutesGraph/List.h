#pragma once
#include <iostream>
#include <exception>
#include <stdexcept>

namespace srg {

	template<typename T>
	class List {			// templated list, has iterators too! (although iterators are not working with the std functions...)
	private:

		struct node {
			T _item;
			node* _next;
			node* _prev;

			node(const T& item, node* next = nullptr, node* prev = nullptr) :
				_item(item), _next(next), _prev(prev)
			{
			}
		};

		node* _head;
		node* _tail;

		void p_insert_to_head(node* node_to_insert)		// privet function for easier writing
		{
			if (is_empty())
				insert_to_empty(node_to_insert);
			else
			{
				node_to_insert->_next = _head;
				_head->_prev = node_to_insert;
				_head = node_to_insert;
			}
		}

		void p_insert_to_tail(node* node_to_insert)		// privet function for easier writing
		{
			if (is_empty())
				insert_to_empty(node_to_insert);
			else
			{
				node_to_insert->_prev = _tail;
				_tail->_next = node_to_insert;
				_tail = node_to_insert;
			}
		}

		void insert_to_empty(node* node_to_insert)
		{
			_head = node_to_insert;
			_tail = node_to_insert;
		}

		void print() const								// for operator<<
		{
			node* temp = _head;

			while (temp != nullptr)
			{
				std::cout << temp->_item << " -> ";
				temp = temp->_next;
			}
		}

		static void list_copy(List& dest, const List& src)	// pretty self explanatory 
		{
			dest.make_empty();								// deletes the list we are going to copy into first so no memory leaks!

			node* temp = src._head;

			while (temp != nullptr)
			{
				dest.insert_to_tail(temp->_item);
				temp = temp->_next;
			}
		}

	public:

		List() : _head(nullptr), _tail(nullptr) {}		// constructors + destructors

		List(const List& other) : List()
		{
			list_copy(*this, other);
		}

		~List() { make_empty(); }

		friend class iterator;

		class iterator {								// very nice iterator
		private:

			friend class List;

			List* _lst;
			node* _ptr;

			iterator(List& lst, node* ptr) : _lst(&lst), _ptr(ptr) {}

		public:

			iterator(List& lst) : _lst(&lst), _ptr(nullptr) {}
			iterator(const iterator& other) : _lst(other._lst), _ptr(other._ptr) {}
			~iterator() { return; }

			iterator& operator=(const iterator& other)
			{
				_ptr = other._ptr;
				_lst = other._lst;

				return *this;
			}

			iterator& operator++()			// make the iterator move up and down the list
			{
				if (_ptr != nullptr)
					_ptr = _ptr->_next;

				return *this;
			}

			iterator operator++(int)
			{
				iterator temp = *this;

				if (_ptr != nullptr)
					_ptr = _ptr->_next;

				return temp;
			}

			iterator& operator--()
			{

				if (_ptr == nullptr)
					_ptr = _lst->_tail;
				else if (_ptr != _lst->_head)
					_ptr = _ptr->_prev;

				return *this;
			}

			iterator operator--(int)
			{
				iterator temp = *this;

				if (_ptr == nullptr)
					_ptr = _lst->_tail;
				else if (_ptr != _lst->_head)
					_ptr = _ptr->_prev;

				return temp;
			}

			T* operator->() { return &_ptr->_item; }		// basic iterator stuff
			T& operator*() { return _ptr->_item; }

			bool operator==(const iterator& other) { return _ptr == other._ptr; }
			bool operator!=(const iterator& other) { return !(*this == other); }

			iterator insert(const T& new_item)				// inserts a item to the iterator location!
			{
				iterator new_itr(*_lst);

				if (_ptr == _lst->_head)
				{
					_lst->insert_to_head(new_item);
					new_itr._ptr = _ptr->_prev;
				}
				else if (_ptr == nullptr)
				{
					_lst->insert_to_tail(new_item);
					new_itr._ptr = _lst->_tail;
				}
				else
				{
					node* new_node = new node(new_item, _ptr, _ptr->_prev);
					_ptr->_prev->_next = new_node;
					new_itr._ptr = _ptr->_prev;
				}

				return new_itr;
			}

			iterator& itr_delete()							// deletes the item the iterator is pointing to
			{
				if (_ptr == _lst->_head)
				{
					_lst->delete_head();
					_ptr = _lst->_head;
				}
				else if (_ptr == _lst->_tail)
				{
					_lst->delete_tail();
					_ptr = nullptr;
				}
				else if (_ptr == nullptr)
					throw std::logic_error("out of bounds");
				else
				{
					node* next = _ptr->_next;
					node* prev = _ptr->_prev;

					next->_prev = prev;
					prev->_next = next;

					delete _ptr;
					_ptr = next;
				}

				return *this;
			}

		};

		class const_iterator {					// very nice const_iterator 
		private:

			friend class List;

			const List* _lst;
			node* _ptr;

			const_iterator(const List& lst, node* ptr) : _lst(&lst), _ptr(ptr) {}

		public:

			const_iterator(const List& lst) : _lst(&lst), _ptr(nullptr) {}
			const_iterator(const const_iterator& other) : _lst(other._lst), _ptr(other._ptr) {}
			~const_iterator() { return; }

			const_iterator& operator=(const const_iterator& other)
			{
				_ptr = other._ptr;
				_lst = other._lst;

				return *this;
			}

			const_iterator& operator++()
			{
				if (_ptr != nullptr)
					_ptr = _ptr->_next;

				return *this;
			}

			const_iterator operator++(int)
			{
				const_iterator temp = *this;

				if (_ptr != nullptr)
					_ptr = _ptr->_next;

				return temp;
			}

			const_iterator& operator--()
			{

				if (_ptr == nullptr)
					_ptr = _lst->_tail;
				else if (_ptr != _lst->_head)
					_ptr = _ptr->_prev;

				return *this;
			}

			const_iterator operator--(int)
			{
				const_iterator temp = *this;

				if (_ptr == nullptr)
					_ptr = _lst->_tail;
				else if (_ptr != _lst->_head)
					_ptr = _ptr->_prev;

				return temp;
			}

			const T* operator->() { return &_ptr->_item; }
			const T& operator*() { return _ptr->_item; }

			bool operator==(const const_iterator& other) { return _ptr == other._ptr; }
			bool operator!=(const const_iterator& other) { return !(*this == other); }

		};

		iterator begin() { return iterator(*this, _head); }					// just like stl!
		iterator end() { return iterator(*this, nullptr); }
		const_iterator begin() const { return const_iterator(*this, _head); }
		const_iterator end() const { return const_iterator(*this, nullptr); }

		bool is_empty() { return _head == nullptr && _tail == nullptr; }
		void make_empty()
		{
			while (_head != nullptr)
			{
				node* temp = _head->_next;
				delete _head;
				_head = temp;
			}

			_tail = nullptr;
		}

		void insert_to_head(const T& new_item)
		{
			node* new_node = new node(new_item);
			p_insert_to_head(new_node);
		}

		void insert_to_tail(const T& new_item)
		{
			node* new_node = new node(new_item);
			p_insert_to_tail(new_node);
		}

		void delete_head()
		{
			if (is_empty())
				throw std::logic_error("tried deleting an empty list");
			else if (_head == _tail)
				make_empty();
			else
			{
				node* temp = _head->_next;
				delete _head;
				_head = temp;
				_head->_prev = nullptr;
			}
		}

		void delete_tail()
		{
			if (is_empty())
				throw std::logic_error("tried deleting an empty list");
			else if (_head == _tail)
				make_empty();
			else
			{
				node* temp = _tail->_prev;
				delete _tail;
				_tail = temp;
				_tail->_next = nullptr;
			}
		}

		List& operator=(const List& other)
		{
			list_copy(*this, other);

			return *this;
		}

		void cat(const List& src)
		{
			node* temp = src._head;

			while (temp != nullptr)
			{
				insert_to_tail(temp->_item);
				temp = temp->_next;
			}
		}

		friend std::ostream& operator<<(std::ostream& os, const List& lst)
		{
			lst.print();

			return os;
		}
	};

}