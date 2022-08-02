#pragma once

namespace ft
{
	template < class T >
	struct Node
	{
		struct Node*	parent;
		struct Node*	left;
		struct Node*	right;
		T*				val;
		bool			color;
	};

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

				mapIterator( Node<T>* node )
				{
					_current = node;
				}

				// DESTRUCTOR
				~mapIterator( void ) {};

				// OPERATOR OVERLOAD
				mapIterator& operator = ( const mapIterator& it)
				{
					if (this != &it)
						_current = it._current;
					return (*this);
				}

				// COMPARISON
				bool	operator == (const mapIterator<const value_type>& it) const
				{
					return (*_current->val == *it);
				}

				bool	operator != (const mapIterator<const value_type>& it) const
				{
					return (!(*this == it));
				}

				// DEREFERENCING
				reference operator * ( void ) const
				{
					return (*_current->val);
				}

				pointer operator -> ( void ) const
				{
					return (_current->val);
				}

				// OPERATIONS

				// PRE/POST INCREMENT
				mapIterator operator ++ ( void )
				{
					mapIterator	tmp(*this);

					if (_current->parent && _current->val > _current->parent->val)
						_current = _current->parent;
					else if (_current->right)
					{
						_current = _current->right;
						while (_current->left)
							_current = _current->left;
					}
					return (tmp);
				}

				mapIterator& operator ++ ( int )
				{
					if (_current->parent && *_current > *_current->parent)
						_current = _current->parent;
					else if (_current->right)
					{
						_current = _current->right;
						while (_current->left)
							_current = _current->left;
					}
					return(_current);
				}

				// PRE/POST DECREMENT
				mapIterator& operator -- ( int )
				{
					mapIterator	tmp(*this);

					if (_current->parent && *_current < *_current->parent)
						_current = _current->parent;
					else if (_current->left)
					{
						_current = _current->left;
						while (_current->right)
							_current = _current->right;
					}
					return (tmp);
				}

				mapIterator operator -- ( void )
				{
					if (_current->parent && *_current < *_current->parent)
						_current = _current->parent;
					else if (_current->left)
					{
						_current = _current->left;
						while (_current->right)
							_current = _current->right;
					}
					return(_current);
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
