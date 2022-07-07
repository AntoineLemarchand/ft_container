#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	template < class T >
		class vectorIterator
		{

			public:
		// CONSTRUCTORS
			typedef	ptrdiff_t	difference_type;
			typedef	T			value_type;
			typedef	T*			pointer;
			typedef	T&			reference;
			vectorIterator( void )
			{
				_pointer = NULL;
			}

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
				if (this != &it)
					_pointer = it.getPointer();
				return (*this);
			}

			// COMPARISON
			bool	operator == (const vectorIterator<value_type>& it)
			{
				return (_pointer == it.getPointer());
			}

			bool	operator != (const vectorIterator<value_type>& it)
			{
				return (_pointer == it.getPointer());
			}

			bool	operator >= (const vectorIterator<value_type>& it)
			{
				return (_pointer == it.getPointer());
			}
			
			bool	operator <= (const vectorIterator<value_type>& it)
			{
				return (_pointer == it.getPointer());
			}
			
			bool	operator > (const vectorIterator<value_type>& it)
			{
				return (_pointer == it.getPointer());
			}
			
			bool	operator < (const vectorIterator<value_type>& it)
			{
				return (_pointer == it.getPointer());
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
				vectorIterator tmp;
				tmp = *this;
				_pointer++;
				return (tmp);
			}

			vectorIterator& operator -- ( int )
			{
				vectorIterator tmp;
				tmp = *this;
				_pointer--;
				return (tmp);
			}

			// DEREFERENCING
			value_type operator * ( void ) const
			{
				return (*_pointer);
			}

			pointer operator -> ( void ) const
			{
				return (_pointer);
			}

			value_type operator [] ( const std::size_t n)
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

			vectorIterator& operator += ( const int n )
			{
				_pointer += n;
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
			
			private:
				pointer	_pointer;
		};
}
