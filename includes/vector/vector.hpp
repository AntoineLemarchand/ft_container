#pragma once
#include "vectorIterator.hpp"

namespace	ft
{
	// T       : vector::value_type
	// Alloc   : vector::allocator_type
	// T&      : vector::reference
	// const T&: vector::const_referenceG
	// T*      : vector::pointer
	// const T*: vector::const_pointer
	template < class T, class Alloc = std::allocator<T> >
		class vector
		{
			public:
				// CONSTRUCTORS
				explicit vector(const Alloc& alloc = Alloc())
				{
					_content = NULL;
					_capacity = 0;
					_size = 0;
					_alloc = alloc;
				}

				explicit vector(std::size_t n, const T& val = T(),
						const Alloc& alloc = Alloc())
				{
					_capacity = n;
					_size = n;
					_alloc = alloc;
					_content = _alloc.allocate(_capacity);
					for (std::size_t i = 0; i < n; i++)
						_alloc.construct(&_content[i], val);
				}

				vector(vectorIterator<T> first, vectorIterator<T> last,
						const Alloc& alloc = Alloc())
					{
						int	i;

						_capacity = 1;
						_alloc = alloc;
						for (vectorIterator<T> it = first; it != last; it++)
							_capacity++;
						_size = _capacity;
						_content =  _alloc.allocate(_capacity);
						i = 0;
						for (vectorIterator<T> it = first; it != last; it++)
						{
							_alloc.construct(&_content[i], *it);
							i++;
						}
					}

				vector(const vector& x)
				{
					int	i;

					_capacity = x.capacity();
					_size = x.size();
					_alloc = x.get_allocator();
					_content = _alloc.allocate(_capacity);
					i = 0;
					for (vectorIterator<T> it = x.begin(); it != x.end(); it++)
					{
						_alloc.construct(&_content[i], *it);
						i++;
					}
				}

				// DESTRUCTOR
				~vector()
				{
					if (_capacity)
					{
						clear();
						_alloc.deallocate(_content, _capacity);
					}
				}

				// OPERATOR=
				vector&	operator= (const vector& x)
				{
					int	i;

					if (this != &x)
					{
						_capacity = x.capacity();
						_size = x.size();
						if (!empty())
							_alloc.deallocate(_content);
						if (!x.empty())
						{
							_alloc = x.get_allocator();
							_content = _alloc.allocate();
							i = 0;
							for (vectorIterator<T> it = x.begin; it != x.end; it++)
							{
								_alloc.construct(_content[i], *it);
								i++;
							}
						}
					}
					return (*this);
				}

				// ITERATORS
				vectorIterator<T> begin() const
				{
					return (vectorIterator<T>(_content));
				}

				vectorIterator<T> end() const
				{
					return (vectorIterator<T>(_content + _size));
				}
				//reverse_vectorIterator rbegin();
				//reverse_vectorIterator rend();


				// CAPACITY
				std::size_t	size() const
				{
					return (_size);
				}

				std::size_t	max_size() const
				{
					return (_alloc.max_size());
				}

				void		resize (std::size_t n, T val = T());

				std::size_t	capacity() const
				{
					return (_capacity);
				}

				bool		empty() const
				{
					return (_size == 0);
				}

				void		reserve (std::size_t n)
				{
					T*	swp;

					if (n > max_size())
						throw std::length_error("vector::reserve");
					if (_capacity < n)
					{
						swp = _alloc.allocate(n);
						for (int i = 0; i < _size; i++)
							_alloc.construct(swp[i], _content[i]);
						_alloc.deallocate(_content);
						_content = swp;
					}
				}

				// ELEMENT ACCESS
				T&			operator[] (std::size_t n)
				{
					return (_content[n]);
				}

				const T&	operator[] (std::size_t n) const
				{
					return (_content[n]);
				}

				T&			at (std::size_t n)
				{
					std::string	err("vector::_M_range_check: __n (which is ");

					if (n > _size)
					{
						err += n;
						err += ">= this->size() (which is ";
						err += _size;
						err += ")";
						throw std::out_of_range(err);
					}
					return (_content[n]);
				}

				const T&	at (std::size_t n) const
				{
					std::string	err("vector::_M_range_check: __n (which is ");

					if (n > _size)
					{
						err += n;
						err += ">= this->size() (which is ";
						err += _size;
						err += ")";
						throw std::out_of_range(err);
					}
					return (_content[n]);
				}

				T&			front()
				{
					return (*_content);
				}

				const T&	front() const
				{
					return (*_content);
				}

				T&			back()
				{
					return (_content[_size]);
				}

				const T&	back() const
				{
					return (_content[_size]);
				}

				// MODIFIERS
				template <class InputIterator>
					void assign (InputIterator first, InputIterator last)
				{
					std::size_t	capa;
					std::size_t	i;

					clear();
					capa = 0;
					for (InputIterator it = first; it != last; it++)
						capa++;
					reserve(capa);
					i = 0;
					for (InputIterator it = first; it != last; it++)
					{
						_alloc.construct(_content[i], *it);
						i++;
					}
				}

				void assign (std::size_t n, const T& val)
				{

					clear();
					reserve(n);
					for (int i = 0; i < n; i++)
						_alloc.construct(_content[i], T(val));
				}

				void push_back (const T& val)
				{
					reserve(_size + 1);
					_content[_size] = val;
					_size++;
				}
				
				void pop_back()
				{
					erase(end());
				}

				vectorIterator<T> insert (vectorIterator<T> position,
						const T& val);

				void insert (vectorIterator<T> position, std::size_t n,
						const T& val);

				template <class InputIterator>
					void insert (vectorIterator<T> position, InputIterator first,
							InputIterator last);

				vectorIterator<T> erase (vectorIterator<T> position)
				{
					vectorIterator<T>	contentEnd(end());
					std::size_t	i = 0;
					std::size_t	j = 0;

					for (vectorIterator<T> it = begin(); it < end(); it++)
					{
						_alloc.construct(&_content[j], _content[i]);
						if (it == position)
							i++;
						i++;
						j++;
					}
					_size--;
					_alloc.destroy(&_content[_size]);
					if (position == contentEnd)
						return (end());
					return (position);
				}

				vectorIterator<T> erase (vectorIterator<T> first,
						vectorIterator<T> last);

				void swap (vectorIterator<T>& x);

				void clear()
				{
					while (_size)
						erase(begin());
				};

				// ALLOCATOR
				Alloc get_allocator() const
				{
					return (_alloc);
				}

			private:
				T*			_content;
				Alloc		_alloc;
				std::size_t	_capacity;
				std::size_t	_size;
		};

	// RELATIONAL ITERATOR
	template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
}
