#pragma once

#include "../utils/iterator_traits.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/is_integral.hpp"

namespace ft
{
	template < class T >
		class vectorIterator
		{
			private:
				T*	_pointer;
			public:
				typedef	typename iterator_traits<T*>::difference_type
					difference_type;
				typedef	typename iterator_traits<T*>::value_type
					value_type;
				typedef	typename iterator_traits<T*>::pointer
					pointer;
				typedef	typename iterator_traits<T*>::reference
					reference;
				typedef typename iterator_traits<T*>::iterator_category
					iterator_category;

				// CONSTRUCTORS
				vectorIterator( void )
				{
					_pointer = NULL;
				}

				vectorIterator( const vectorIterator<value_type>& it):
					_pointer(&(*it))
				{}

				vectorIterator( pointer ptr )
				{
					_pointer = ptr;
				}

				vectorIterator( const reference ref )
				{
					_pointer = &ref;
				}

				// DESTRUCTOR
				~vectorIterator( void ) {}

				// OPERATOR OVERLOAD
				vectorIterator& operator = ( const vectorIterator<T>& it)
				{
					if (this != &it)
						_pointer = &(*it);
					return (*this);
				}

				// COMPARISON
				bool	operator == (const vectorIterator<T>& it)
				{
					return (_pointer == &(*it));
				}

				bool	operator == (const vectorIterator<const T>& it) const
				{
					return (_pointer == &(*it));
				}

				bool	operator != (const vectorIterator<T>& it)
				{
					return (_pointer != &(*it));
				}

				bool	operator != (const vectorIterator<const T>& it) const
				{
					return (_pointer != &(*it));
				}

				bool	operator >= (const vectorIterator<T>& it)
				{
					return (_pointer >= &(*it));
				}

				bool	operator >= (const vectorIterator<const T>& it) const
				{
					return (_pointer >= &(*it));
				}

				bool	operator <= (const vectorIterator<T>& it)
				{
					return (_pointer <= &(*it));
				}

				bool	operator <= (const vectorIterator<const T>& it) const
				{
					return (_pointer <= &(*it));
				}

				bool	operator > (const vectorIterator<T>& it)
				{
					return (_pointer > &(*it));
				}

				bool	operator > (const vectorIterator<const T>& it) const
				{
					return (_pointer > &(*it));
				}

				bool	operator < (const vectorIterator<T>& it)
				{
					return (_pointer < &(*it));
				}

				bool	operator < (const vectorIterator<const T>& it) const
				{
					return (_pointer < &(*it));
				}

				// DEREFERENCING
				reference operator * ( void ) const
				{
					return (*_pointer);
				}

				pointer operator -> ( void ) const
				{
					return (_pointer);
				}

				reference operator [] ( const std::size_t n )
				{
					return (*(_pointer + n));
				}

				// OPERATIONS

				// ADDITION
				vectorIterator operator + ( difference_type n ) const
				{
					return (vectorIterator(_pointer + n));
				}

				difference_type operator + ( const vectorIterator& it) const
				{
					return (reinterpret_cast<long>(_pointer)
							+ reinterpret_cast<long>(&(*it)));
				}

				vectorIterator& operator += ( const int n )
				{
					_pointer += n;
					return (*this);
				}

				friend vectorIterator operator + (difference_type n,
						vectorIterator& it)
				{
					return (vectorIterator(n + it._pointer));
				}

				// PRE/POST INCREMENT
				vectorIterator& operator ++ ( void )
				{
					++_pointer;
					return (*this);
				}

				vectorIterator operator ++ ( int )
				{
					vectorIterator tmp(*this);
					_pointer++;
					return (tmp);
				}
				// SUBSTRACTION
				vectorIterator operator - ( const int n ) const
				{
					return (vectorIterator(_pointer - n));
				}

				difference_type operator - ( const vectorIterator& it) const
				{
					return (_pointer - &(*it));
				}

				vectorIterator& operator -= ( const int n )
				{
					_pointer -= n;
					return (*this);
				}

				friend vectorIterator operator - (difference_type n,
						vectorIterator& it)
				{
					return (vectorIterator(n - it._pointer));
				}

				// PRE/POST DECREMENT
				vectorIterator operator -- ( int )
				{
					vectorIterator tmp(*this);
					_pointer--;
					return (tmp);
				}

				vectorIterator& operator -- ( void )
				{
					--_pointer;
					return (*this);
				}
		};

	template < class T >
		class reverse_vectorIterator
		{
			private:
				vectorIterator<T>	_it;
			public:
				typedef vectorIterator<T> iterator_type;
				typedef typename
					iterator_traits<vectorIterator<T> >::iterator_category
					iterator_category;
				typedef typename
					iterator_traits<vectorIterator<T> >::value_type
					value_type;
				typedef typename
					iterator_traits<vectorIterator<T> >::difference_type
					difference_type;
				typedef typename
					iterator_traits<vectorIterator<T> >::pointer
					pointer;
				typedef typename
					iterator_traits<vectorIterator<T> >::reference
					reference;


				reverse_vectorIterator( void )
				{
					_it = vectorIterator<T>();
				}

				explicit reverse_vectorIterator(iterator_type it)
				{
					_it = it;
				}

				template <class Iter>
					reverse_vectorIterator<T>
					(const reverse_vectorIterator<Iter>& rev_it)
					{
						_it = rev_it.base();
					}

				reverse_vectorIterator<T>& operator =
					( const reverse_vectorIterator<T>& rit)
				{
					if (this != &rit)
						_it = rit.base();
					return (*this);
				}

				// DEREFERENCE
				iterator_type base() const
				{
					return (_it);
				}

				reference operator * ( void ) const
				{
					return (*(_it - 1));
				}

				pointer operator->() const
				{
					return (&(**this));
				}

				reference operator [] (difference_type n) const
				{
					return (base()[-n - 1]);
				}

				// COMPARISON
				bool	operator ==
					(const reverse_vectorIterator<const value_type>& it) const
				{
					return (_it == it.base());
				}

				bool	operator !=
					(const reverse_vectorIterator<const value_type>& it) const
				{
					return (_it != it.base());
				}

				bool	operator <
					(const reverse_vectorIterator<const value_type>& it) const
				{
					return (_it > it.base());
				}

				bool	operator <=
					(const reverse_vectorIterator<const value_type>& it) const
				{
					return (_it >= it.base());
				}

				bool	operator >
					(const reverse_vectorIterator<const value_type>& it) const
				{
					return (_it < it.base());
				}

				bool	operator >=
					(const reverse_vectorIterator<const value_type>& it) const
				{
					return (_it <= it.base());
				}

				// ADDITION
				reverse_vectorIterator<T> operator + (difference_type n) const
				{
					return (reverse_vectorIterator(_it - n));
				}

				difference_type operator +
					(const reverse_vectorIterator<T>& n) const
				{
					return (-(_it + n.base()));
				}

				friend reverse_vectorIterator<T> operator +
					(difference_type n, const reverse_vectorIterator<T>& rev_it)
				{
					return (reverse_vectorIterator<T>(rev_it._it - n));
				}

				reverse_vectorIterator<T>& operator+= (difference_type n)
				{
					_it -= n;
					return (*this);
				}

				// PRE/POST INCREMENT
				reverse_vectorIterator<T>& operator++( void )
				{
					--_it;
					return (*this);
				}

				reverse_vectorIterator<T>  operator++(int)
				{
					reverse_vectorIterator<T> tmp(*this);
					_it--;
					return (tmp);
				}

				//SUBSTRACTION
				friend reverse_vectorIterator<T> operator -
					(difference_type n, const reverse_vectorIterator<T>& rev_it)
				{
					return (reverse_vectorIterator<T>(rev_it._it + n));
				}

				reverse_vectorIterator<T> operator - (difference_type n) const
				{
					return (reverse_vectorIterator(_it + n));
				}

				difference_type operator -
					(const reverse_vectorIterator<T>& n) const
				{
					return (-(_it - n.base()));
				}

				reverse_vectorIterator<T>& operator-= (difference_type n)
				{
					_it += n;
					return (*this);
				}

				// PRE/POST DECREMENT
				reverse_vectorIterator<T>& operator--( void )
				{
					++_it;
					return (*this);
				}

				reverse_vectorIterator<T>  operator--(int)
				{
					reverse_vectorIterator<T> tmp(*this);
					_it++;
					return (tmp);
				}
		};
}

