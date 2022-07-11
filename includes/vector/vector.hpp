#pragma once
#include "vectorIterator.hpp"
#include "../enable_if.hpp"
#include "../is_integral.hpp"
#include "../equal.hpp"
#include "../lexicographical_compare.hpp"

namespace	ft
{
	template < class T, class Alloc = std::allocator<T> >
		class vector
		{
			public:
				typedef	T        value_type;
				typedef	Alloc    allocator_type;
				typedef	T&       reference;
				typedef	const T& const_reference;
				typedef	T*       pointer;
				typedef	const T* const_pointer;
				typedef	vectorIterator<value_type>       iterator;
				typedef	vectorIterator<const value_type>	const_iterator;
				typedef	reverse_vectorIterator<value_type>	reverse_iterator;
				typedef	reverse_vectorIterator<const value_type>	const_reverse_iterator;
				typedef	std::ptrdiff_t	difference_type;
				typedef	std::size_t	size_type;

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
					for (size_type i = 0; i < n; i++)
						_alloc.construct(&_content[i], val);
				}


				template <class InputIterator>
					vector (InputIterator first,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last,
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
						for (iterator it = x.begin();
								it < x.end(); it++)
							push_back(*it);
					}
					return (*this);
				}

				// ITERATORS
				iterator begin() const
				{
					return (iterator(_content));
				}

				iterator end() const
				{
					return (iterator(_content + _size));
				}

				reverse_iterator rbegin()
				{
					return (reverse_iterator(end() - 1));
				}

				reverse_iterator rend()
				{
					return (reverse_iterator(begin() - 1));
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
							typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
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
					iterator	ret;
					pointer		newContent;
					size_type	i = 0;

					if (_size == _capacity)
						newContent = _alloc.allocate(_capacity + 1);
					else
						newContent = _alloc.allocate(_capacity);
					for (iterator it = begin(); it < position; it++)
					{
						_alloc.construct(&newContent[i], *it);
						i++;
					}
					_alloc.construct(&newContent[i], val);
					ret = iterator(&newContent[i]);
					for (iterator it = position; it < end(); it++)
					{
						_alloc.construct(&newContent[i + 1], *it);
						i++;
					}
					clear();
					_alloc.deallocate(_content, _capacity);
					_size++;
					if (_capacity < _size)
						_capacity++;
					return (ret);
				}

				void insert (iterator position, size_type n,
						const_reference val)
				{
					pointer		newContent;
					size_type	i = 0;

					if (_capacity < _size + n)
						newContent = _alloc.allocate(_capacity + n);
					else
						newContent = _alloc.allocate(_capacity);
					for (iterator it = begin(); it < position; it++)
					{
						_alloc.construct(&newContent[i], *it);
						i++;
					}
					for (size_type n2 = n; n2; n2--)
					{
						_alloc.construct(&newContent[i], val);
						i++;
					}
					for (iterator it = position; it < end(); it++)
					{
						_alloc.construct(&newContent[i + n], *it);
						i++;
					}
					clear();
					_alloc.deallocate(_content, _capacity);
					_size += n;
					if (_capacity < _size)
						_capacity += n;
				}

				template <class InputIterator>
					void insert (iterator position, InputIterator first,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
					{
						pointer		newContent;
						size_type	i = 0;
						size_type	j = 0;

						for (InputIterator it = first; it != last; it++)
							j++;
						if (_capacity < _size + j)
							newContent = _alloc.allocate(_capacity + j);
						else
							newContent = _alloc.allocate(_capacity);
						for (iterator it = begin(); it < position; it++)
						{
							_alloc.construct(&newContent[i], *it);
							i++;
						}
						for (InputIterator it = first; it != last; it++)
							_alloc.construct(&newContent[i], *it);
						for (iterator it = position; it < end(); it++)
						{
							_alloc.construct(&newContent[i + j], *it);
							i++;
						}
						clear();
						if (!empty())
							_alloc.deallocate(_content, _capacity);
						_size += j;
						if (_capacity < _size)
							_capacity += j;
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
					int i = 0;
					int j = 0;

					for (iterator it = begin(); it < first; it++)
						i++;
					for (iterator it = first; it < last; it++)
						j++;
					for (iterator it = last; it < end(); it++)
						_content[i] = _content[i + j];
					while (j)
					{
						pop_back();
						j--;
					}
					return (&_content[i]);
				}

				void swap (vector& x)
				{
					pointer		tmp = NULL;
					size_type	capa_tmp = x.capacity();
					size_type	size_tmp = x.size();

					if (*this == x)
						return;
					if (x.capacity())
					{
						tmp = _alloc.allocate(x.capacity());
						for (size_type i = 0; i < x.size(); i++)
							_alloc.construct(&tmp[i], x[i]);
						x.clear();
						x.get_allocator().deallocate(&(*x.begin()),
							x.capacity());
					}
					if (_capacity)
					{
						x.reserve(_capacity);
						for (iterator it = begin(); it != end(); it++)
							x.push_back(*it);
						clear();
						_alloc.deallocate(_content, _capacity);
					}
					_capacity = capa_tmp;
					if (capa_tmp)
					{
						_content = _alloc.allocate(capa_tmp);
						for (size_type i = 0; i < size_tmp; i++)
							push_back(tmp[i]);
					}
					else
						_content = NULL;
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
		bool operator== (const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			return (equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs)
		{
			return (!(lhs == rhs));
		}

	template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs)
		{
			return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
						rhs.end()));
		}

	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs)
		{
			return (lhs == rhs || lhs < rhs);
		}

	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs)
		{
			return (!lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
						rhs.end()));
		}

	template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs,
				const vector<T,Alloc>& rhs)
		{
			return (lhs == rhs || lhs > rhs);
		}

	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
}
