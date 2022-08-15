#pragma once
#include "../utils/iterator_traits.hpp"

namespace ft
{
	struct Node
	{
		struct Node*	parent;
		struct Node*	left;
		struct Node*	right;
		void*			val;
		std::size_t		color;

		Node()
		{
			parent = NULL;
			left = NULL;
			right = NULL;
			val = NULL;
			color = 0;
		}
	};

	template < class T >
		class mapIterator
		{
			private:
				const Node* _current;
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

				operator mapIterator<const T>() const
				{
					return (mapIterator<const T>(*this->_current));
				}

				// CONSTRUCTORS
				mapIterator( void )
				{
					_current = NULL;
				}

				mapIterator( const mapIterator& it)
				{
					*this = it;
				}

				mapIterator( const Node& node )
				{
					_current = &node;
				}

				// DESTRUCTOR
				~mapIterator( void )
				{
				};

				// OPERATOR OVERLOAD
				mapIterator& operator = ( const mapIterator& it)
				{
					if (this != &it)
						_current = it.getCurrent();
					return (*this);
				}

				// COMPARISON
				bool	operator == (const mapIterator<const value_type>& it)
					const
				{
					return (_current == it.getCurrent());
				}

				bool	operator != (const mapIterator<const value_type>& it)
					const
				{
					return (!(*this == it));
				}

				bool	operator == (const mapIterator<value_type>& it)
				{
					return (_current->val == &(*it));
				}

				bool	operator != (const mapIterator<value_type>& it)
				{
					return (!(*this == it));
				}

				// DEREFERENCING
				reference operator * ( void ) const
				{
					return (*static_cast<value_type*>(_current->val));
				}

				pointer operator -> ( void ) const
				{
					return (static_cast<value_type*>(_current->val));
				}

				// OPERATIONS

				// PRE/POST INCREMENT
				mapIterator operator ++ ( void )
				{
					mapIterator	tmp(*this);
					const Node*		prev;

					if (_current->right)
					{
						prev = _current;
						_current = _current->right;
						if (_current->val != NULL && prev->val != NULL)
							while (_current->left)
								_current = _current->left;
					}
					else
					{
						while (_current->parent
								&& _current == _current->parent->right)
							_current = _current->parent;
						_current = _current->parent;
					}
					return (tmp);
				}

				mapIterator& operator ++ ( int )
				{
					const Node*	prev;

					if (_current->right)
					{
						prev = _current;
						_current = _current->right;
						if (_current->val != NULL && prev->val != NULL)
							while (_current->left)
								_current = _current->left;
					}
					else
					{
						while (_current->parent
								&& _current == _current->parent->right)
							_current = _current->parent;
						_current = _current->parent;
					}
					return(*this);
				}

				// PRE/POST DECREMENT
				mapIterator operator -- ( int )
				{
					mapIterator	tmp(*this);
					const Node*	prev;

					if (_current->left)
					{
						prev = _current;
						_current = _current->left;
						if (_current->val != NULL && prev->val != NULL)
							while (_current->right)
								_current = _current->right;
					}
					else
					{
						while (_current->parent
								&& _current == _current->parent->left)
							_current = _current->parent;
						_current = _current->parent;
					}
					return (tmp);
				}

				mapIterator& operator -- ( void )
				{
					const Node*	prev;

					if (_current->left)
					{
						prev = _current;
						_current = _current->left;
						if (_current->val != NULL && prev->val != NULL)
							while (_current->right)
								_current = _current->right;
					}
					else
					{
						while (_current->parent
								&& _current == _current->parent->left)
							_current = _current->parent;
						_current = _current->parent;
					}
					return(*this);
				}

				const Node*	getCurrent() const
				{
					return (_current);
				}
		};

	template < class T >
		class reverse_mapIterator
		{
			private:
				mapIterator<T>	_it;
			public:
				typedef mapIterator<T> iterator_type;
				typedef typename
					iterator_traits<mapIterator<T> >::iterator_category
					iterator_category;
				typedef typename
					iterator_traits<mapIterator<T> >::value_type
					value_type;
				typedef typename
					iterator_traits<mapIterator<T> >::difference_type
					difference_type;
				typedef typename
					iterator_traits<mapIterator<T> >::pointer
					pointer;
				typedef typename
					iterator_traits<mapIterator<T> >::reference
					reference;

				reverse_mapIterator( void )
				{
					_it = iterator_type();
				}

				explicit reverse_mapIterator(iterator_type it)
				{
					_it = it;
				}

				template <class Iter>
					reverse_mapIterator<T>
					(const reverse_mapIterator<Iter>& rev_it)
					{
						_it = rev_it.base();
					}

				reverse_mapIterator<T>& operator =
					( const reverse_mapIterator<T>& rit)
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
				bool	operator ==
					(const reverse_mapIterator<const value_type>& it) const
				{
					return (_it == it.base());
				}

				bool	operator !=
					(const reverse_mapIterator<const value_type>& it) const
				{
					return (_it != it.base());
				}

				bool	operator <
					(const reverse_mapIterator<const value_type>& it) const
				{
					return (_it > it.base());
				}

				bool	operator <=
					(const reverse_mapIterator<const value_type>& it) const
				{
					return (_it >= it.base());
				}

				bool	operator >
					(const reverse_mapIterator<const value_type>& it) const
				{
					return (_it < it.base());
				}

				bool	operator >=
					(const reverse_mapIterator<const value_type>& it) const
				{
					return (_it <= it.base());
				}

				// PRE/POST INCREMENT
				reverse_mapIterator<T>& operator ++ ( void )
				{
					--_it;
					return (*this);
				}

				reverse_mapIterator<T>  operator ++ (int)
				{
					reverse_mapIterator<T> tmp(*this);
					_it--;
					return (tmp);
				}

				// PRE/POST DECREMENT
				reverse_mapIterator<T>& operator -- ( void )
				{
					++_it;
					return (*this);
				}

				reverse_mapIterator<T>  operator -- (int)
				{
					reverse_mapIterator<T> tmp(*this);
					_it++;
					return (tmp);
				}
		};
}
