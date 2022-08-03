#pragma once

#include "../utils/redBlackTree.hpp"

namespace ft
{
	template < class T >
		class mapIterator
		{
			private:
				typedef Node<T> node_type;
				node_type*	_currentNode;
				T*			_current;	
			public:
				typedef	typename iterator_traits<T*>::difference_type	difference_type;
				typedef	typename iterator_traits<T*>::value_type		value_type;
				typedef	typename iterator_traits<T*>::pointer			pointer;
				typedef	typename iterator_traits<T*>::reference			reference;
				typedef typename iterator_traits<T*>::iterator_category	iterator_category;

				// CONSTRUCTORS
				mapIterator( void )
				{
					_currentNode = NULL;
					_current = NULL;
				}

				mapIterator( const mapIterator<value_type>& it)
				{
					*this = it;
				}

				mapIterator( const node_type* node)
				{
					_currentNode = node;
				}

				// DESTRUCTOR
				~mapIterator( void ) {};

				// OPERATOR OVERLOAD
				mapIterator& operator = ( const mapIterator& it)
				{
					if (this != &it)
					{
						_currentNode = it._current;
						_current = NULL;
					}
					return (*this);
				}

				// COMPARISON
				bool	operator == (const mapIterator<const value_type>& it) const
				{
					return (_current == *it);
				}

				bool	operator != (const mapIterator<const value_type>& it) const
				{
					return (_current != *it);
				}

				// DEREFERENCING
				reference operator * ( void ) const
				{
					return (_current);
				}

				pointer operator -> ( void ) const
				{
					return (&_current);
				}

				// OPERATIONS

				// PRE/POST INCREMENT
				mapIterator operator ++ ( void )
				{
					mapIterator	tmp(*this);

					if (_currentNode->parent && _current->val > _current->parent->val)
						_currentNode = _current->parent;
					else if (_currentNode->right)
					{
						_currentNode = _current->right;
						while (_currentNode->left)
							_currentNode = _current->left;
					}
					_current = _currentNode->val;
					return (_current);
				}

				mapIterator& operator ++ ( int )
				{
					if (_currentNode->parent && *_current > *_current->parent)
						_currentNode = _current->parent;
					else if (_currentNode->right)
					{
						_currentNode = _current->right;
						while (_currentNode->left)
							_currentNode = _current->left;
					}
					return(_currentNode);
				}

				// PRE/POST DECREMENT
				mapIterator& operator -- ( int )
				{
					mapIterator	tmp(*this);

					if (_currentNode->parent && *_current < *_current->parent)
						_currentNode = _current->parent;
					else if (_currentNode->left)
					{
						_currentNode = _current->left;
						while (_currentNode->right)
							_currentNode = _current->right;
					}
					return (tmp);
				}

				mapIterator operator -- ( void )
				{
					if (_currentNode->parent && *_current < *_current->parent)
						_currentNode = _current->parent;
					else if (_currentNode->left)
					{
						_currentNode = _current->left;
						while (_currentNode->right)
							_currentNode = _current->right;
					}
					return(_currentNode);
				}
		};

	template < class T >
		class reverse_mapIterator
		{
			private:
				mapIterator<T>	_it;
			public:
				typedef vectorIterator<T> iterator_type;
				typedef typename iterator_traits<vectorIterator<T> >::iterator_category iterator_category;
				typedef typename iterator_traits<vectorIterator<T> >::value_type value_type;
				typedef typename iterator_traits<vectorIterator<T> >::difference_type difference_type;
				typedef typename iterator_traits<vectorIterator<T> >::pointer pointer;
				typedef typename iterator_traits<vectorIterator<T> >::reference reference;

				reverse_mapIterator( void )
				{
					_it = mapIterator<T>();
				}

				explicit reverse_mapIterator(iterator_type it)
				{
					_it = it;
				}

				template <class Iter>
					reverse_mapIterator<T> (const reverse_mapIterator<Iter>& rev_it)
					{
						_it = rev_it.base();
					}

				reverse_mapIterator<T>& operator = ( const reverse_mapIterator<T>& rit)
				{
					if (this != &rit)
						_it = rit.base();
					return (*this);
				}

				// DEREFERENCE
				mapIterator<T> base() const
				{
					return (_it);
				}

				reference operator * ( void ) const
				{
					mapIterator<T> retVal(_it);
					retVal--;

					return (*retVal);
				}

				pointer operator->() const
				{
					return (&(**this));
				}

				// COMPARISON
				bool	operator == (const reverse_mapIterator<const value_type>& it) const
				{
					return (_it == it.base());
				}

				bool	operator != (const reverse_mapIterator<const value_type>& it) const
				{
					return (_it != it.base());
				}

				bool	operator < (const reverse_mapIterator<const value_type>& it) const
				{
					return (_it > it.base());
				}

				bool	operator <= (const reverse_mapIterator<const value_type>& it) const
				{
					return (_it >= it.base());
				}

				bool	operator > (const reverse_mapIterator<const value_type>& it) const
				{
					return (_it < it.base());
				}

				bool	operator >= (const reverse_mapIterator<const value_type>& it) const
				{
					return (_it <= it.base());
				}

				// PRE/POST INCREMENT
				reverse_mapIterator<T>& operator++( void )
				{
					--_it;
					return (*this);
				}

				reverse_mapIterator<T>  operator++(int)
				{
					reverse_mapIterator<T> tmp(*this);
					_it--;
					return (tmp);
				}

				// PRE/POST DECREMENT
				reverse_mapIterator<T>& operator--( void )
				{
					++_it;
					return (*this);
				}

				reverse_mapIterator<T>  operator--(int)
				{
					reverse_mapIterator<T> tmp(*this);
					_it++;
					return (tmp);
				}
		};
}
