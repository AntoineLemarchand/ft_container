#pragma once

#include "mapIterator.hpp"
#include "../utils/redBlackTree.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
			 class Alloc = std::allocator<pair<const Key,T> > > class map
			 {
				 private:
					 typedef	Node<pair<const Key, T> >		node_type;

					 Alloc									_alloc;
					 Compare								_comp;
					 redBlackTree<Key, T, Compare, Alloc>	_tree;
				 public:
					 // MEMBER TYPES
					 //		BASIC
					 typedef Key										key_type;
					 typedef T											mapped_type;
					 typedef pair<const key_type, mapped_type>			value_type;
					 typedef Compare									key_compare;
					 typedef Alloc										allocator_type;
					 typedef typename allocator_type::reference			reference;
					 typedef typename allocator_type::const_reference	const_reference;
					 typedef typename allocator_type::pointer			pointer;
					 typedef typename allocator_type::const_pointer		const_pointer;
					 //		ITERATORS
					 typedef mapIterator<value_type>					iterator;
					 typedef mapIterator<const value_type>				const_iterator;
					 typedef reverse_mapIterator<value_type>			reverse_iterator;
					 typedef reverse_mapIterator<const value_type>		const_reverse_iterator;
					 typedef std::ptrdiff_t								difference_type;
					 typedef std::size_t								size_type;

					 class value_compare
					 {
						 friend class map;
						 protected:
						 Compare comp;
						 value_compare (Compare c) : comp(c) {}
						 public:
						 typedef bool result_type;
						 typedef value_type first_argument_type;
						 typedef value_type second_argument_type;

						 bool operator() (const value_type&x,
								 const value_type& y) const
						 {
							 return comp(x.first, y.first);
						 }
					 };

					 // CONSTRUCTORS
					 explicit map (const key_compare& comp = key_compare(),
							 const allocator_type& alloc = allocator_type())
					 {
						 _alloc = alloc;
						 _comp = comp;
					 }
					 template <class InputIterator>
						 map (InputIterator first,
								 typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last,
								 const key_compare& comp = key_compare(),
								 const allocator_type& alloc = allocator_type())
						 {
							 _comp = comp;
							 _alloc = alloc;
							 insert(first, last);
						 }

					 map (const map& x)
					 {
						 _alloc = x.get_allocator();
						 _comp = x.key_comp();
						 for (mapIterator<value_type> it = x.begin(); it != x.end(); it++)
							 _tree.insertNode(*it);
					 }

					 // DESTRUCTOR
					 ~map() {};

					 // OPERATOR=
					 map& operator= (const map& x)
					 {
						 if (this != &x)
						 {
							 clear();
							 for (mapIterator<value_type> it = x.begin();
									 it != x.end(); it++)
								 _tree.insertNode(*it);
							 _comp = x.key_comp();
						 }
						 return (*this);
					 }

					 // ITERATORS
					 iterator begin()
					 {
						 iterator	ret = _tree.getRoot();

						 while (ret->left)
							 ret = ret->left;
						 return (ret);
					 }

					 const_iterator begin() const
					 {
						 node_type*	ret = _tree.getRoot();

						 while (ret->left)
							 ret = ret->left;
						 return (ret);
					 }

					 iterator end()
					 {
						 iterator	ret = _tree.getRoot();

						 while (ret->right)
							 ret = ret->right;
						 return (*(&(ret) + 1));
					 }

					 const_iterator end() const
					 {
						 const_iterator	ret = _tree.getRoot();

						 while (ret->right)
							 ret = ret->right;
						 return (*(&(ret) + 1));
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
					 bool empty() const
					 {
						 return (!_tree.getRoot());
					 }

					 size_type size() const
					 {
						 return (_tree.getSize());
					 }

					 size_type max_size() const
					 {
						 return (_alloc.max_size());
					 }

					 // ELEMENT ACCESS
					 mapped_type& operator[] (const key_type& k)
					 {
						 iterator	ret = begin();

						 while (k)
							 ret++;
						 return (*ret);
					 }

					 // MODIFIERS
					 pair<iterator,bool> insert (const value_type& val)
					 {
						 Node<value_type>*	N;
						 bool				is_inserted;

						 N = _tree.searchTree(_tree.getRoot(), val.first);
						 if (!N)
						 {
							 _tree.insertNode(val);
							 is_inserted = true;
							 N = _tree.searchTree(_tree.getRoot(), val.first);
						 }
						 else
							 is_inserted = false;
						 return (make_pair(iterator(N->val), is_inserted));
					 }

					 iterator insert (iterator position, const value_type& val)
					 {
						 Node<value_type>*	N;

						 N = _tree.searchTree(position, val.first);
						 if (!N)
							 N = _tree.searchTree(_tree.getRoot(), val.first);
						 if (!N)
						 {
							 _tree.insertNode(val);
							 N = _tree.searchTree(position, val.first);
							 if (!N)
								 N = _tree.searchTree(_tree.getRoot(), val.first);
						 }
						 return (iterator(N->val));
					 }

					 template <class InputIterator>
						 void insert (InputIterator first, InputIterator last)
						 {
							 for (InputIterator it = first; it != last; it++)
								 _tree.insertNode(*it);
						 }

					 void erase (iterator position)
					 {
						 _tree.deleteNode(searchTree(_tree.getRoot(),
									 *position.first));
					 }

					 size_type erase (const key_type& k)
					 {
						 Node<value_type>*	toDel;

						 toDel = searchTree(_tree.getRoot(), k);
						 if (!toDel)
							 return (0);
						 _tree.deleteNode(toDel);
						 return (1);
					 }

					 void erase (iterator first, iterator last)
					 {
						 for (iterator it = first; it != last; it++)
							 deleteNode(searchTree(_tree.getRoot(), *it.first));
					 }

					 void swap (map& x)
					 {
						 (void)x;
					 }

					 void clear()
					 {
						 _tree.clearNode(_tree.getRoot());
					 }

					 // OBSERVERS
					 key_compare key_comp() const
					 {
						 return (_comp);
					 }

					 value_compare value_comp() const
					 {
						 value_compare	ret;
						 return (ret);
					 }

					 // OPERATIONS
					 iterator find (const key_type& k)
					 {
						 Node<value_type>*	ret;

						 ret = _tree.searchTree(_tree.getRoot(), k);
						 if (!ret)
							 return (end());
						 return (iterator(ret));
					 }

					 const_iterator find (const key_type& k) const
					 {
						 Node<value_type>*	ret;

						 ret = _tree.searchTree(_tree.getRoot(), k);
						 if (!ret)
							 return (end());
						 return (const_iterator(ret));
					 }

					 size_type count (const key_type& k) const
					 {
						 if (find(k) != end())
							 return (1);
						 return (0);
					 }

					 iterator lower_bound (const key_type& k)
					 {
						 Node<value_type>* N = _tree.getRoot();
						 value_type	prev;

						 if (N->val.first > k)
						 {
							 while (N && N->val.first > k)
							 {
								 prev = N->val;
								 N = N->left;
							 }
							 while (N && N->val.first > k)
							 {
								 prev = N->val;
								 N = N->right;
							 }
							 return (iterator(prev));
						 }
						 else if (N->val.first < k)
						 {
							 while (N && N->val.first <= k)
								 N = N->left;
							 while (N && N->val.first <= k)
								 N = N->right;
							 return (iterator(N->val));
						 }
						 return(iterator(N->val));
					 }

					 const_iterator lower_bound (const key_type& k) const
					 {
						 Node<value_type>* N = _tree.getRoot();
						 value_type prev;

						 if (N->val.first > k)
						 {
							 while (N && N->val.first > k)
							 {
								 prev = N->val;
								 N = N->left;
							 }
							 while (N && N->val.first > k)
							 {
								 prev = N->val;
								 N = N->right;
							 }
							 return (const_iterator(prev));
						 }
						 else if (N->val.first < k)
						 {
							 while (N && N->val.first <= k)
								 N = N->left;
							 while (N && N->val.first <= k)
								 N = N->right;
							 return (const_iterator(N->val));
						 }
						 return(const_iterator(N->val));
					 }

					 iterator upper_bound (const key_type& k)
					 {
						 Node<value_type>* N = _tree.getRoot();
						 value_type prev;

						 if (N->val.first <= k)
						 {
							 prev = N->val;
							 while (N && N->val.first <= k)
							 {
								 value_type prev = N->val;
								 N = N->right;
							 }
							 while (N && N->val.first <= k)
							 {
								 value_type prev = N->val;
								 N = N->left;
							 }
							 return (iterator(prev));
						 }
						 else if (N->val.first > k)
						 {
							 while (N && N->val.first > k)
								 N = N->left;
							 while (N && N->val.first > k)
								 N = N->right;
							 return (iterator(N->val));
						 }
						 return(iterator(N->val));
					 }

					 const_iterator upper_bound (const key_type& k) const
					 {
						 Node<value_type>* N = _tree.getRoot();
						 value_type prev;

						 if (N->val.first <= k)
						 {
							 prev = N->val;
							 while (N && N->val.first <= k)
							 {
								 value_type prev = N->val;
								 N = N->right;
							 }
							 while (N && N->val.first <= k)
							 {
								 value_type prev = N->val;
								 N = N->left;
							 }
							 return (const_iterator(prev));
						 }
						 else if (N->val.first > k)
						 {
							 while (N && N->val.first > k)
								 N = N->left;
							 while (N && N->val.first > k)
								 N = N->right;
							 return (const_iterator(N->val));
						 }
						 return(const_iterator(N->val));
					 }

					 pair<const_iterator,const_iterator> equal_range (const key_type& k) const
					 {
						 return(make_pair(lower_bound(k), upper_bound(k)));
					 }

					 pair<iterator,iterator>             equal_range (const key_type& k)
					 {
						 return(make_pair(lower_bound(k), upper_bound(k)));
					 }

					 // ALLOCATOR
					 allocator_type get_allocator() const
					 {
						 return (_alloc);
					 }
			 };
}
