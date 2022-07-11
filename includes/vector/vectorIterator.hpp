#pragma once

#include "../iterator_traits.hpp"

namespace ft
{
	template < class T >
		class vectorIterator
		{
			private:
				T*	_pointer;
			public:
				typedef	typename iterator_traits<T*>::difference_type	difference_type;
				typedef	typename iterator_traits<T*>::value_type			value_type;
				typedef	typename iterator_traits<T*>::pointer			pointer;
				typedef	typename iterator_traits<T*>::reference		reference;
				typedef typename iterator_traits<T*>::iterator_category iterator_category;

				// CONSTRUCTORS
				vectorIterator( void )
				{
					_pointer = NULL;
				}

//				operator vectorIterator<const T>() const
//				{
//					return (vectorIterator<const T>(_pointer));
//				}

				vectorIterator( const vectorIterator<value_type>& it)
				{
					_pointer = it.getPointer();
				}

				vectorIterator( pointer ptr )
				{
					_pointer = ptr;
				}

				// DESTRUCTOR
				~vectorIterator( void ) {}
				
				// OPERATOR OVERLOAD
				vectorIterator& operator = (const vectorIterator<value_type>& it)
				{
					_pointer = it.getPointer();
					return (*this);
				}

				// COMPARISON
				bool	operator == (const vectorIterator<const value_type>& it) const
				{
					return (_pointer == it.getPointer());
				}

				bool	operator != (const vectorIterator<const value_type>& it) const
				{
					return (_pointer != it.getPointer());
				}

				bool	operator >= (const vectorIterator<const value_type>& it) const
				{
					return (_pointer >= it.getPointer());
				}

				bool	operator <= (const vectorIterator<const value_type>& it) const
				{
					return (_pointer >= it.getPointer());
				}

				bool	operator > (const vectorIterator<const value_type>& it) const
				{
					return (_pointer > it.getPointer());
				}

				bool	operator < (const vectorIterator<const value_type>& it) const
				{
					return (_pointer < it.getPointer());
				}

				// PRE INCREMENT/DECREMENT
				vectorIterator& operator ++ ( void )
				{
					++_pointer;
					return (*this);
				}

				vectorIterator& operator -- ( void )
				{
					--_pointer;
					return (*this);
				}

				// POST INCREMENT/DECREMENT
				vectorIterator operator ++ ( int )
				{
					vectorIterator tmp(*this);
					_pointer++;
					return (tmp);
				}

				vectorIterator operator -- ( int )
				{
					vectorIterator tmp(*this);
					_pointer--;
					return (tmp);
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

				reference operator [] ( const std::size_t n)
				{
					return (_pointer + n);
				}

				// OPERATIONS

				vectorIterator operator + ( const int n ) const
				{
					return (vectorIterator(_pointer + n));
				}

				vectorIterator operator - ( const int n ) const
				{
					return (vectorIterator(_pointer - n));
				}

				difference_type operator + ( const vectorIterator& it) const
				{
					return (_pointer + it.getPointer());
				}

				difference_type operator - ( const vectorIterator& it) const
				{
					return (_pointer - it.getPointer());
				}

				vectorIterator& operator += ( const int n )
				{
					_pointer -= n;
					return (*this);
				}

				vectorIterator& operator -= ( const int n )
				{
					_pointer += n;
					return (*this);
				}

				// OTHER MEMBER
				pointer	getPointer( void ) const
				{
					return (_pointer);
				}
		};

	template < class T >
		class reverse_vectorIterator
		{
			private:
				vectorIterator<T>	_it;
			public:
				typedef vectorIterator<T> iterator_type;
				typedef typename iterator_traits<vectorIterator<T> >::iterator_category iterator_category;
				typedef typename iterator_traits<vectorIterator<T> >::value_type value_type;
				typedef typename iterator_traits<vectorIterator<T> >::difference_type difference_type;
				typedef typename iterator_traits<vectorIterator<T> >::pointer pointer;
				typedef typename iterator_traits<vectorIterator<T> >::reference reference;

				reverse_vectorIterator( void )
				{
					_it = vectorIterator<T>();
				}

				explicit reverse_vectorIterator(iterator_type it)
				{
					_it = it;
				}

				template <class Iter>
					reverse_vectorIterator<T> (const reverse_vectorIterator<Iter>& rev_it)
					{
						_it = rev_it.base();
					}

				operator reverse_vectorIterator<const T>() const
				{
					return (reverse_vectorIterator<const T>(_it.getPointer()));
				}

				vectorIterator<T> base() const
				{
					return (_it);
				}

				reference operator * ( void ) const
				{
					return (*_it);
				}

				bool	operator == (const reverse_vectorIterator<const value_type>& it) const
				{
					return (_it == it.base());
				}

				bool	operator != (const reverse_vectorIterator<const value_type>& it) const
				{
					return (_it != it.base());
				}

				reverse_vectorIterator<T> operator + (difference_type n)
				{
					return (reverse_vectorIterator(_it - n));
				}

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

				reverse_vectorIterator<T>& operator+= (difference_type n)
				{
					_it -= n;
					return (*this);
				}

				reverse_vectorIterator<T> operator - (difference_type n)
				{
					return (reverse_vectorIterator(_it + n));
				}

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

				reverse_vectorIterator<T>& operator-= (difference_type n)
				{
					return (_it += n);
				}

				pointer operator->() const
				{
					return (_it->a);
				}

				reference operator[] (difference_type n) const
				{
					return (_it - n - 1);
				}
		};
}
