#pragma once
#include "../utils/iterator_traits.hpp"

namespace ft
{
	struct setNode
	{
		struct setNode*	parent;
		struct setNode*	left;
		struct setNode*	right;
		void*			val;
		std::size_t		color;

		setNode()
		{
			parent = NULL;
			left = NULL;
			right = NULL;
			val = NULL;
			color = 0;
		}
	};

	template < class T >
		class setIterator
		{
			private:
				const setNode* _current;
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

				operator setIterator<const T>() const
				{
					return (setIterator<const T>(*this->_current));
				}

				// CONSTRUCTORS
				setIterator( void )
				{
					_current = NULL;
				}

				setIterator( const setIterator& it)
				{
					*this = it;
				}

				setIterator( const setNode& node )
				{
					_current = &node;
				}

				// DESTRUCTOR
				~setIterator( void )
				{
				};

				// OPERATOR OVERLOAD
				setIterator& operator = ( const setIterator& it)
				{
					if (this != &it)
						_current = it.getCurrent();
					return (*this);
				}

				// COMPARISON
				bool	operator == (const setIterator<const value_type>& it)
					const
					{
						return (_current == it.getCurrent());
					}

				bool	operator != (const setIterator<const value_type>& it)
					const
					{
						return (!(*this == it));
					}

				bool	operator == (const setIterator<value_type>& it)
				{
					return (_current->val == &(*it));
				}

				bool	operator != (const setIterator<value_type>& it)
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
				setIterator& operator ++ ( void )
				{
					const setNode*	prev;

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

				setIterator operator ++ ( int )
				{
					setIterator		tmp(*this);
					const setNode*		prev;

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

				// PRE/POST DECREMENT
				setIterator& operator -- ( void )
				{
					const setNode*	prev;

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

				setIterator operator -- ( int )
				{
					setIterator	tmp(*this);
					const setNode*	prev;

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

				const setNode*	getCurrent() const
				{
					return (_current);
				}
		};

	template < class T >
		class reverse_setIterator
		{
			private:
				setIterator<T>	_it;
			public:
				typedef setIterator<T> iterator_type;
				typedef typename
					iterator_traits<setIterator<T> >::iterator_category
					iterator_category;
				typedef typename
					iterator_traits<setIterator<T> >::value_type
					value_type;
				typedef typename
					iterator_traits<setIterator<T> >::difference_type
					difference_type;
				typedef typename
					iterator_traits<setIterator<T> >::pointer
					pointer;
				typedef typename
					iterator_traits<setIterator<T> >::reference
					reference;

				reverse_setIterator( void )
				{
					_it = iterator_type();
				}

				explicit reverse_setIterator(iterator_type it)
				{
					_it = it;
				}

				template <class Iter>
					reverse_setIterator<T>
					(const reverse_setIterator<Iter>& rev_it)
					{
						_it = rev_it.base();
					}

				reverse_setIterator<T>& operator =
					( const reverse_setIterator<T>& rit)
					{
						if (this != &rit)
							_it = rit.base();
						return (*this);
					}

				// DEREFERENCE
				setIterator<T> base() const
				{
					return (_it);
				}

				reference operator * ( void ) const
				{
					setIterator<T> retVal(_it);
					retVal--;
					return (*retVal);
				}

				pointer operator->() const
				{
					return (&(**this));
				}

				// COMPARISON
				bool	operator ==
					(const reverse_setIterator<const value_type>& it) const
					{
						return (_it == it.base());
					}

				bool	operator !=
					(const reverse_setIterator<const value_type>& it) const
					{
						return (_it != it.base());
					}

				bool	operator <
					(const reverse_setIterator<const value_type>& it) const
					{
						return (_it > it.base());
					}

				bool	operator <=
					(const reverse_setIterator<const value_type>& it) const
					{
						return (_it >= it.base());
					}

				bool	operator >
					(const reverse_setIterator<const value_type>& it) const
					{
						return (_it < it.base());
					}

				bool	operator >=
					(const reverse_setIterator<const value_type>& it) const
					{
						return (_it <= it.base());
					}

				// PRE/POST INCREMENT
				reverse_setIterator<T>& operator ++ ( void )
				{
					--_it;
					return (*this);
				}

				reverse_setIterator<T>  operator ++ (int)
				{
					reverse_setIterator<T> tmp(*this);
					_it--;
					return (tmp);
				}

				// PRE/POST DECREMENT
				reverse_setIterator<T>& operator -- ( void )
				{
					++_it;
					return (*this);
				}

				reverse_setIterator<T>  operator -- (int)
				{
					reverse_setIterator<T> tmp(*this);
					_it++;
					return (tmp);
				}
		};
}
