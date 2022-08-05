#pragma once

#include "mapIterator.hpp"
#include "../utils/pair.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
			 class Alloc = std::allocator<pair<const Key,T> > > class map
			 {
				 private:
					 std::allocator<Node> _nodeAlloc;
					 Alloc			_alloc;
					 Compare		_comp;
					 std::size_t	_size;
					 Node*			_root;
					 Node*			_leaf;

					 // TREE UTILS
					 void	clearNode(Node* node)
					 {
						 _size--;
						 if (node && node != _leaf && node->left)
							 clearNode(node->left);
						 if (node && node != _leaf && node->right)
							 clearNode(node->right);
						 if (node && node != _leaf)
						 {
							 _alloc.destroy(static_cast<pair<const Key, T>* >(node->val));
							 _alloc.deallocate(static_cast<pair<const Key, T>* >(node->val), 1);
							 _nodeAlloc.destroy(node);
							 _nodeAlloc.deallocate(node, 1);
						 }
						 _nodeAlloc.destroy(_leaf);
						 _nodeAlloc.deallocate(_leaf, 1);
					 }

					 Node* getMinimum(Node* N) const
					 {
						 while (N->left && N->left != _leaf)
							 N = N->left;
						 return (N);
					 }

					 Node* getMaximum(Node* N) const
					 {
						 while (N->right && N->right != _leaf)
							 N = N->right;
						 return (N);
					 }

					 Node*	searchTree(Node* root, Key key) const
					 {
						 if (root == NULL || root == _leaf
								 || static_cast<value_type*>(root->val)->first == key)
							 return (root);
						 if (static_cast<value_type*>(root->val)->first < key)
							 return (searchTree(root->right, key));
						 return (searchTree(root->left, key));
					 }


					 // NODE DELETION
					 void shiftNode(Node* to, Node* from)
					 {
						 if (from->parent)
						 {
							 if (from->parent->right == from)
								 from->parent->right = NULL;
							 else
								 from->parent->left = NULL;
						 }
						 to->val = from->val;
						 _nodeAlloc.destroy(from);
						 _nodeAlloc.deallocate(from, 1);
					 }

					 //using
					 //https://medium.com/analytics-vidhya/deletion-in-red-black-rb-tree-92301e1474ea
					 void deleteNode(Node* N)
					 {
						 if (!N)
							 return;
						 // if node is red, perform a classic bst delete
						 if (N->right && N->left)
							 shiftNode(N, getMinimum(N->right));
						 else if (N->right)
							 shiftNode(N, N->right);
						 else if (N->left)
							 shiftNode(N, N->left);
						 else
						 {
							 if (!N->parent)
								 _root = NULL;
							 if (N->parent->left == N)
								 N->parent->left = NULL;
							 else
								 N->parent->right = NULL;
							 _nodeAlloc.destroy(N);
							 _nodeAlloc.deallocate(N, 1);
						 }
					 }

					 // NODE INSERTION
					 // classic BST insert
					 Node*	tree_insert(Node* root, Node* prev,
							 pair<const Key, T> val)
					 {
						 if (!root || root == _leaf)
						 {
							 Node tmp;

							 // initializing node
							 root = _nodeAlloc.allocate(1);
							 _nodeAlloc.construct(root, tmp);
							 root->val = _alloc.allocate(1);
							 _alloc.construct(static_cast<value_type*>(root->val), val);
							 root->parent = prev;
							 root->left = NULL;
							 root->right = NULL;
							 root->color = 0;
							 if (!_root)
								 _root = root;
						 }
						 else if (val.first > static_cast<value_type*>(root->val)->first)
							 root->right = tree_insert(root->right, root, val);
						 else if (val.first < static_cast<value_type*>(root->val)->first)
							 root->left = tree_insert(root->left, root, val);
						 return (root);
					 }

					 /* to go from           to     */
					 /*     l                  r    */
					 /*    / \                / \   */
					 /*  l1   r              l  r2  */
					 /*      / \            / \   \ */
					 /*     r1 r2          l1 r1  r2*/
					 void	leftRotate(Node* l)
					 {
						 Node*	r;

						 r = l->right;
						 if (l->parent && l->parent->right == l)
							 l->parent->right = r;
						 else if (l->parent)
							 l->parent->left = r;
						 else
							 _root = r;
						 r->parent = l->parent;
						 l->right = r->left;
						 if (l->right)
							 l->right->parent = l;
						 r->left = l;
						 l->parent = r;
					 }

					 /* to go from           to     */
					 /*     r                  l    */
					 /*    / \                / \   */
					 /*   l  r2             l1   r  */
					 /*  / \   \                / \ */
					 /* l1 r1  r2              r1 r2*/
					 void	rightRotate(Node* r)
					 {
						 Node*	l;

						 l = r->left;
						 if (r->parent && r->parent->right == r)
							 r->parent->right = l;
						 else if (r->parent)
							 r->parent->left = l;
						 else
							 _root = l;
						 l->parent = r->parent;
						 r->left = l->right;
						 if (r->left)
							 r->left->parent = r;
						 l->right = r;
						 r->parent = l;
					 }
					 //source
					 //https://en.wikipedia.org/wiki/Red%E2%80%93black_tree#Insertion
					 void	RBT_fixInsert(Node* N)
					 {
						 Node* P = N->parent; //parent
						 Node* G; //grandparent
						 Node* U; // uncle

						 _root->color = 1;
						 while (P)
						 {
							 if (!P || P->color == 1)
								 return;
							 if ((G = P->parent) == NULL)
							 {
								 P->color = 1;
								 break;
							 }
							 U = (G->right == P) ? G->left : G->right;
							 if (!U || U->color == 1)
							 {
								 if (N == P->right && P == G->left)
								 {
									 leftRotate(P);
									 N = P;
									 P = G->left;
								 }
								 else if (N == P->left && P == G->right)
								 {
									 rightRotate(P);
									 N = P;
									 P = G->right;
								 }
								 if (N == P->left)
									 rightRotate(G);
								 else
									 leftRotate(G);
								 P->color = 1;
								 G->color = 0;
								 break;
							 }
							 P->color = 1;
							 U->color = 1;
							 G->color = 0;
							 N = G;
							 P = N->parent;
						 }
						 while (_root->parent)
							 _root = _root->parent;
						 if (N == _root)
						 {
							 N->left = _leaf;
							 N->right = _leaf;
						 }
						 else if (N == getMinimum(_root))
							 N->left = _leaf;
						 else
							 N->right = _leaf;
						 _leaf->left = getMaximum(_root);
						 _leaf->right = getMinimum(_root);
					 }

					 void insertNode(const pair<const Key, T>& val)
					 {
						 _size++;
						 while (_root && _root->parent)
							 _root = _root->parent;
						 if (!_root)
							 tree_insert(_root, NULL, val);
						 else
						 {
							 tree_insert(_root, NULL, val);
							 RBT_fixInsert(searchTree(_root, val.first));
						 }
					 }

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
						 _size = 0;
						 _root = NULL;
						 _leaf = _nodeAlloc.allocate(1);
						 _nodeAlloc.construct(_leaf, Node());
						 _leaf->color = 2;
					 }

					 template <class InputIterator>
						 map (InputIterator first, InputIterator last,
								 const key_compare& comp = key_compare(),
								 const allocator_type& alloc = allocator_type())
						 {
							 _size = 0;
							 _root = NULL;
							 _comp = comp;
							 _alloc = alloc;
							 _leaf = _nodeAlloc.allocate(1);
							 _nodeAlloc.construct(_leaf, Node());
							 _leaf->color = 2;
							 insert(first, last);
							 _leaf->right = getMinimum(_root);
							 _leaf->left = getMaximum(_root);
							 getMinimum(_root)->left = _leaf;
							 getMaximum(_root)->right = _leaf;
						 }

					 map (const map& x)
					 {
						 _size = 0;
						 _root = NULL;
						 _alloc = x.getallocator();
						 _comp = x.key_comp();
						 _leaf = _nodeAlloc.allocate(1);
						 _nodeAlloc.construct(_leaf, Node());
						 _leaf->color = 2;
						 insert(x.begin(), x.end());
						 _leaf->right = getMinimum(_root);
						 _leaf->left = getMaximum(_root);
						 getMinimum(_root)->left = _leaf;
						 getMaximum(_root)->right = _leaf;
					 }

					 // DESTRUCTOR
					 ~map()
					 {
						 clear();
					 };

					 // OPERATOR=
					 map& operator= (const map& x)
					 {
						 if (this != &x)
						 {
							 clear();
							 _comp = x.key_comp();
							 insert(x.begin(), x.end());
							 _leaf->right = getMinimum(_root);
							 _leaf->left = getMaximum(_root);
							 getMinimum(_root)->left = _leaf;
							 getMaximum(_root)->right = _leaf;
						 }
						 return (*this);
					 }

					 // ITERATORS
					 iterator begin()
					 {
						 return (iterator(*getMinimum(_root)));
					 }

					 const_iterator begin() const
					 {
						 return (const_iterator(*getMinimum(_root)));
					 }

					 iterator end()
					 {
						 return (iterator(*(getMaximum(_root) + 1)));
					 }

					 const_iterator end() const
					 {
						 return (const_iterator(*(getMaximum(_root) + 1)));
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
						 return (!_root);
					 }

					 size_type size() const
					 {
						 return (_size);
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
						 Node*	N;
						 bool	is_inserted;

						 N = searchTree(_root, val->first);
						 if (!N)
						 {
							 insertNode(val);
							 is_inserted = true;
							 N = searchTree(_root, val->first);
						 }
						 else
							 is_inserted = false;
						 return (make_pair(iterator(N->val), is_inserted));
					 }

					 iterator insert (iterator position, const value_type& val)
					 {
						 Node*	N;

						 N = searchTree(position, val->first);
						 if (!N)
							 N = searchTree(_root, val->first);
						 if (!N)
						 {
							 insertNode(val);
							 N = searchTree(position, val->first);
							 if (!N)
								 N = searchTree(_root, val->first);
						 }
						 return (iterator(N->val));
					 }

					 template <class InputIterator>
						 void insert (InputIterator first, InputIterator last)
						 {
							 for (InputIterator it = first; it != last; it++)
								 insertNode(*it);
						 }

					 void erase (iterator position)
					 {
						 deleteNode(searchTree(_root, *position.first));
					 }

					 size_type erase (const key_type& k)
					 {
						 Node*	toDel;

						 toDel = searchTree(_root, k);
						 if (!toDel)
							 return (0);
						 deleteNode(toDel);
						 return (1);
					 }

					 void erase (iterator first, iterator last)
					 {
						 for (iterator it = first; it != last; it++)
							 deleteNode(searchTree(_root, *it.first));
					 }

					 void swap (map& x)
					 {
						 (void)x;
					 }

					 void clear()
					 {
						 clearNode(_root);
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
						 Node*	ret;

						 ret = searchTree(_root, k);
						 if (!ret)
							 return (end());
						 return (iterator(ret));
					 }

					 const_iterator find (const key_type& k) const
					 {
						 Node*	ret;

						 ret = searchTree(_root, k);
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
						 Node* N = _root;
						 Node* prev;

						 if (static_cast<value_type*>(N->val)->first > k)
						 {
							 while (N && static_cast<value_type*>(N->val)->first > k)
							 {
								 prev = N;
								 N = N->left;
							 }
							 while (N && static_cast<value_type*>(N->val)->first > k)
							 {
								 prev = N;
								 N = N->right;
							 }
							 return (iterator(*prev));
						 }
						 else if (static_cast<value_type*>(N->val)->first < k)
						 {
							 while (N && static_cast<value_type*>(N->val)->first <= k)
								 N = N->left;
							 while (N && static_cast<value_type*>(N->val)->first <= k)
								 N = N->right;
							 return (iterator(*N));
						 }
						 return(iterator(*N));
					 }

					 const_iterator lower_bound (const key_type& k) const
					 {
						 Node* N = _root;
						 Node* prev = _root;

						 if (static_cast<value_type*>(N->val)->first > k)
						 {
							 while (N && static_cast<value_type*>(N->val)->first > k)
							 {
								 prev = N;
								 N = N->left;
							 }
							 while (N && static_cast<value_type*>(N->val)->first > k)
							 {
								 prev = N;
								 N = N->right;
							 }
							 return (const_iterator(*prev));
						 }
						 else if (static_cast<value_type*>(N->val)->first < k)
						 {
							 while (N && static_cast<value_type*>(N->val)->first <= k)
								 N = N->left;
							 while (N && static_cast<value_type*>(N->val)->first <= k)
								 N = N->right;
							 return (const_iterator(*N));
						 }
						 return(const_iterator(*N));
					 }

					 iterator upper_bound (const key_type& k)
					 {
						 Node* N = _root;
						 Node* prev;

						 if (static_cast<value_type*>(N->val)->first <= k)
						 {
							 prev = N;
							 while (N && static_cast<value_type*>(N->val)->first <= k)
							 {
								 prev = N;
								 N = N->right;
							 }
							 while (N && static_cast<value_type*>(N->val)->first <= k)
							 {
								 prev = N;
								 N = N->left;
							 }
							 return (iterator(*prev));
						 }
						 else if (static_cast<value_type*>(N->val)->first > k)
						 {
							 while (N && static_cast<value_type*>(N->val)->first > k)
								 N = N->left;
							 while (N && static_cast<value_type*>(N->val)->first > k)
								 N = N->right;
							 return (iterator(*N));
						 }
						 return(iterator(*N));
					 }

					 const_iterator upper_bound (const key_type& k) const
					 {
						 Node* N = _root;
						 Node* prev = _root;

						 if (static_cast<value_type*>(N->val)->first <= k)
						 {
							 prev = N;
							 while (N && static_cast<value_type*>(N->val)->first <= k)
							 {
								 prev = N;
								 N = N->right;
							 }
							 while (N && static_cast<value_type*>(N->val)->first <= k)
							 {
								 prev = N;
								 N = N->left;
							 }
							 return (const_iterator(*prev));
						 }
						 else if (static_cast<value_type*>(N->val)->first > k)
						 {
							 while (N && static_cast<value_type*>(N->val)->first > k)
								 N = N->left;
							 while (N && static_cast<value_type*>(N->val)->first > k)
								 N = N->right;
							 return (const_iterator(*N));
						 }
						 return(const_iterator(*N));
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
					 allocator_type getallocator() const
					 {
						 return (_alloc);
					 }

			 };
}
