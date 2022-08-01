#pragma once

#include "../utils/redBlackTree.hpp"

namespace ft
{
	template < class T >
		class mapIterator
		{
			private:
				Node<T>* _current;
			public:
				typedef	typename iterator_traits<T*>::difference_type	difference_type;
				typedef	typename iterator_traits<T*>::value_type		value_type;
				typedef	typename iterator_traits<T*>::pointer			pointer;
				typedef	typename iterator_traits<T*>::reference			reference;
				typedef typename iterator_traits<T*>::iterator_category	iterator_category;

				// CONSTRUCTORS
				mapIterator( void )
				{
					_current = NULL;
				}

				mapIterator( const mapIterator<value_type>& it)
				{
					*this = it;
				}

				// DESTRUCTOR
				~mapIterator( void ) {};

				// OPERATOR OVERLOAD
				mapIterator& operator = ( const mapIterator& it)
				{
					_current = it.current;
				}

				// COMPARISON
				bool	operator == (const mapIterator<const value_type>& it) const
				{
					return (_current == it.current);
				}

				bool	operator != (const mapIterator<const value_type>& it) const
				{
					return (_current != it.current);
				}

				// DEREFERENCING
				reference operator * ( void ) const
				{
					return (_current->val);
				}

				pointer operator -> ( void ) const
				{
					return (&_current->val);
				}

				reference operator [] ( const std::size_t n );

				// OPERATIONS

				// PRE/POST INCREMENT
				mapIterator& operator ++ ( void );
				mapIterator operator ++ ( int );

				// PRE/POST DECREMENT
				mapIterator operator -- ( int );
				mapIterator& operator -- ( void );
		};
}
