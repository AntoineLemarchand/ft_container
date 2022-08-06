#pragma once
#include "vectorIterator.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/is_integral.hpp"
#include "../utils/equal.hpp"
#include "../utils/lexicographical_compare.hpp"

namespace	ft
{
	template < class T, class Alloc = std::allocator<T> >
		class vector
		{
			public:
				typedef	T
					value_type;
				typedef	Alloc
					allocator_type;
				typedef	T&
					reference;
				typedef	const T&
					const_reference;
				typedef	T*
					pointer;
				typedef	const T*
					const_pointer;
				typedef	vectorIterator<value_type>
					iterator;
				typedef	vectorIterator<const value_type>
					const_iterator;
				typedef	reverse_vectorIterator<value_type>
					reverse_iterator;
				typedef	reverse_vectorIterator<const value_type>
					const_reverse_iterator;
				typedef	std::ptrdiff_t
					difference_type;
				typedef	std::size_t
					size_type;

				// CONSTRUCTORS
				explicit vector(const allocator_type& alloc = Alloc())
				{
					_content = NULL;
					_capacity = 0;
					_size = 0;
					_alloc = alloc;
				}

				explicit vector(size_type n, const_reference val = value_type(),
						const allocator_type& alloc = Alloc())
				{
					_capacity = n;
					_size = n;
					_alloc = alloc;
					_content = _alloc.allocate(_capacity);
					for (size_type i = 0; i < _capacity; i++)
						_alloc.construct(&_content[i], val);
				}


				template <class InputIterator>
					vector (InputIterator first,
							typename ft::enable_if<
							!ft::is_integral<InputIterator>::value,
							InputIterator>::type last,
							const allocator_type& alloc = allocator_type())
					{

						_capacity = 0;
						_size = 0;
						_alloc = alloc;
						_content = NULL;
						for (InputIterator it = first; it != last; it++)
							push_back(*it);
					}

				vector(const vector& x)
				{
					int	i;

					_capacity = x.size();
					_size = x.size();
					_alloc = allocator_type(x.get_allocator());
					_content = _alloc.allocate(_capacity);
					i = 0;
					for (const_iterator it = x.begin(); it != x.end(); it++)
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
					if (this != &x)
					{
						clear();
						reserve(x.size());
						for (const_iterator it = x.begin();
								it < x.end(); it++)
							push_back(*it);
					}
					return (*this);
				}

				// ITERATORS
				iterator begin()
				{
					return (iterator(_content));
				}

				const_iterator begin() const
				{
					return (const_iterator(_content));
				}

				iterator end()
				{
					return (iterator(_content + _size));
				}

				const_iterator end() const
				{
					return (const_iterator(_content + _size));
				}

				reverse_iterator rbegin()
				{
					return (reverse_iterator(end()));
				}

				const_reverse_iterator rbegin() const
				{
					return (const_reverse_iterator(end()));
				}

				reverse_iterator rend()
				{
					return (reverse_iterator(begin()));
				}

				const_reverse_iterator rend() const
				{
					return (const_reverse_iterator(begin()));
				}

				// CAPACITY
				size_type	size() const
				{
					return (_size);
				}

				size_type	max_size() const
				{
					return (_alloc.max_size());
				}

				void		resize (size_type n, value_type val = T())
				{
					while (n < _size)
						pop_back();
					if (n > _capacity && n <= _size * 2)
						reserve(_size * 2);
					else if (n > _capacity)
						reserve(n);
					while (n > _size)
					{
						push_back(val);
					}
				}

				size_type	capacity() const
				{
					return (_capacity);
				}

				bool		empty() const
				{
					return (_size == 0);
				}

				void		reserve (size_type n)
				{
					pointer	swp;

					if (n > max_size())
						throw std::length_error("vector::reserve");
					if (_capacity < n)
					{
						swp = _alloc.allocate(n);
						for (size_type i = 0; i < _size; i++)
						{
							_alloc.construct(&swp[i], _content[i]);
							_alloc.destroy(&_content[i]);
						}
						if (_capacity)
							_alloc.deallocate(_content, _capacity);
						_content = swp;
						_capacity = n;
					}
				}

				// ELEMENT ACCESS
				reference			operator[] (size_type n)
				{
					return (_content[n]);
				}

				const_reference	operator[] (size_type n) const
				{
					return (_content[n]);
				}

				reference			at (size_type n)
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

				const_reference	at (size_type n) const
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

				reference			front()
				{
					return (*_content);
				}

				const_reference	front() const
				{
					return (*_content);
				}

				reference			back()
				{
					return (_content[_size - 1]);
				}

				const_reference	back() const
				{
					return (_content[_size - 1]);
				}

				// MODIFIERS
				template <class InputIterator>
					void assign (InputIterator first,
							typename ft::enable_if<
							!ft::is_integral<InputIterator>::value,
							InputIterator>::type last)
					{
						clear();
						for (InputIterator it = first; it != last; it++)
							push_back(*it);
					}

				void assign (size_type n, const_reference val)
				{

					clear();
					for (size_type i = 0; i < n; i++)
						push_back(val);
				}

				void push_back (const_reference val)
				{
					if (_capacity < _size + 1 && _size != 0)
						reserve(_size * 2);
					else if (_size == 0)
						reserve(_size + 1);
					_alloc.construct(_content + _size, val);
					_size++;
				}

				void pop_back()
				{
					if (!empty())
					{
						_alloc.destroy(_content + _size - 1);
						_size--;
					}
				}

				iterator insert (iterator position, const_reference val)
				{
					value_type	swp;
					size_type	val_ret = 0;

					if (position != end())
					{
						for (iterator it = begin(); it != position; it++)
							val_ret++;
						push_back(val);
						for (size_type i = _size - 1; i > val_ret; i--)
						{
							swp = _content[i];
							_content[i] = _content[i - 1];
							_content[i - 1] = swp;
						}
						return (iterator(_content + val_ret));
					}
					push_back(val);
					return (end() - 1);
				}

				void insert (iterator position, size_type n,
						const_reference val)
				{
					while (n)
					{
						position = insert(position, val);
						n--;
					}
				}

				template <class InputIterator>
					void insert (iterator position, InputIterator first,
							typename ft::enable_if<
							!ft::is_integral<InputIterator>::value,
							InputIterator>::type last)
					{
						for (InputIterator it = first; it != last; it++)
							position = insert(position, *it) + 1;
					}

				iterator erase (iterator position)
				{
					size_type i = 0;
					iterator ret;

					for (iterator it = begin(); it < position; it++)
						i++;
					if (i < _size)
						ret = position;
					else
						ret = end();
					for (iterator it = position + 1; it < end(); it++)
					{
						_content[i] = _content[i + 1];
						i++;
					}
					pop_back();
					return (ret);
				}

				iterator erase (iterator first, iterator last)
				{
					int	i = 0;
					for (iterator it = first; it != last; it++)
						i++;
					while (i)
					{
						erase(first);
						i--;
					}
					return (first);
				}

				void swap (vector& x)
				{
					pointer		tmp = _content;
					size_type	capa_tmp = _capacity;
					size_type	size_tmp = _size;

					if (*this == x)
						return;
					_content = x._content;
					_capacity = x._capacity;
					_size = x._size;
					x._content = tmp;
					x._capacity = capa_tmp;
					x._size = size_tmp;
				}

				void clear()
				{
					if (!empty())
					{
						for (size_type i = 0; i < _size; i++)
							_alloc.destroy(&_content[i]);
					}
					_size = 0;
				};

				// ALLOCATOR
				Alloc get_allocator() const
				{
					return (_alloc);
				}

			private:
				pointer		_content;
				Alloc		_alloc;
				size_type	_capacity;
				size_type	_size;
		};

	// RELATIONAL ITERATOR
	template <class T, class Alloc>
		bool operator == (const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			return (equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

	template <class T, class Alloc>
		bool operator != (const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs)
		{
			return (!(lhs == rhs));
		}

	template <class T, class Alloc>
		bool operator <  (const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs)
		{
			return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
						rhs.end()) && lhs != rhs);
		}

	template <class T, class Alloc>
		bool operator <= (const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs)
		{
			return (lhs == rhs || lhs < rhs);
		}

	template <class T, class Alloc>
		bool operator >  (const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs)
		{
			return (!(lhs <= rhs));
		}

	template <class T, class Alloc>
		bool operator >= (const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs)
		{
			return (!(lhs < rhs));
		}

	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
		{
			x.swap(y);
		}
}
