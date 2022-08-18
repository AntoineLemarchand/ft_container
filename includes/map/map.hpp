#pragma once

#include "mapIterator.hpp"
#include "../utils/pair.hpp"
#include "../utils/lexicographical_compare.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
			 class Alloc = std::allocator<pair<const Key,T> > > class map
			 {
				 private:
					 typename Alloc::template rebind<Node >::other	_nodeAlloc;
					 Alloc			_alloc;
					 Compare		_comp;
					 std::size_t	_size;
					 Node*			_root;
					 Node*			_leaf;

					 // TREE UTILS
					 void	clearNode(Node* node)
					 {
						 _size--;
						 if (node && node != _leaf)
						 {
							 if (node->left && node->left != _leaf)
								 clearNode(node->left);
							 if (node->right && node->right != _leaf)
								 clearNode(node->right);
							 _alloc.destroy(static_cast<pair<const Key, T>* >
									 (node->val));
							 _alloc.deallocate(static_cast<pair<const Key, T>* >
									 (node->val), 1);
							 _nodeAlloc.destroy(node);
							 _nodeAlloc.deallocate(node, 1);
						 }
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
								 || static_cast<value_type*>
								 (root->val)->first == key)
							 return (root);
						 if (_comp(static_cast<value_type*>(root->val)->first, key))
							 return (searchTree(root->right, key));
						 return (searchTree(root->left, key));
					 }

					 /* to go from           to     */
					 /*     l                  r    */
					 /*    / \                / \   */
					 /*  l1   r              l  r2  */
					 /*      / \            / \   \ */
					 /*     r1 r2          l1 r1  r2*/
					 void	leftRotate(Node* P)
					 {
						 Node* N = P->right;
						 Node* tmp;

						 if (N->left && N->left != _leaf)
							 N->left->parent = P;
						 // rotating parents
						 N->parent = P->parent;
						 if (!P->parent)
							 _root = N;
						 else if (P->parent->right == P)
							 P->parent->right = N;
						 else
							 P->parent->left = N;
						 P->parent = N;

						 // and childs
						 tmp = N->left;
						 N->left = P;
						 P->right = tmp;
					 }

					 /* to go from           to     */
					 /*     r                  l    */
					 /*    / \                / \   */
					 /*   l  r2             l1   r  */
					 /*  / \                    / \ */
					 /* l1 l2                  l2 r2*/
					 void	rightRotate(Node* P)
					 {
						 Node* N = P->left;
						 Node* tmp;

						 if (N->right && N->right != _leaf)
							 N->right->parent = P;
						 // rotating parents
						 N->parent = P->parent;
						 if (!P->parent)
							 _root = N;
						 else if (P->parent->right == P)
							 P->parent->right = N;
						 else
							 P->parent->left = N;
						 P->parent = N;

						 // and childs
						 tmp = N->right;
						 N->right = P;
						 P->left = tmp;
					 }

					 // NODE DELETION
					 void swapVal(Node* n1, Node* n2)
					 {
						 Node* tmp;
						 Node* tmp2;
						 std::size_t ctmp;

						 // switching parents
						 tmp = n1->parent;
						 tmp2 = n2->parent;
						 n2->parent = tmp;
						 n1->parent = tmp2;
						 if (!tmp)
							 _root = n2;
						 else if (tmp->right == n1)
							 tmp->right = n2;
						 else
							 tmp->left = n2;
						 if (!tmp2)
							 _root = n1;
						 else if (tmp2->right == n2)
							 tmp2->right = n1;
						 else
							 tmp2->left = n1;
						 // and childs
						 tmp = n1->left;
						 tmp2 = n1->right;
						 n1->left = n2->left;
						 n1->right = n2->right;
						 n2->left = tmp;
						 n2->right = tmp2;
						 if (n1->left && n1->left != _leaf)
							 n1->left->parent = n1;
						 if (n1->right && n1->right != _leaf)
							 n1->right->parent = n1;
						 if (n2->left && n2->left != _leaf)
							 n2->left->parent = n2;
						 if (n2->right && n2->right != _leaf)
							 n2->right->parent = n2;
						 // swap color
						 ctmp = n1->color;
						 n1->color = n2->color;
						 n2->color = ctmp;
					 }

					 // thanks god
					 // https://www.youtube.com/watch?v=CTvfzU_uNKE
					 void RBT_delete(Node* P, Node* S)
					 {
						 Node*	Sl;
						 Node*	Sr;
						 bool	SlColor;
						 bool	SrColor;

						 // case 1
						 while (P)
						 {
							 if (S && S != _leaf)
							 {
								 Sl = S->left;
								 Sr = S->right;
							 }
							 SlColor = (!S || S == _leaf || !Sl
									 || Sl == _leaf || Sl->color == 1);
							 SrColor = (!S || S == _leaf || !Sr ||
									 Sr == _leaf || Sr->color == 1);

							 // case 2
							 if (P->color == 1 && S && S->color == 0
									 && SlColor == 1 && SrColor == 1)
							 {
								 P->color = 0;
								 S->color = 1;
								 if (S == P->left)
								 {
									 S = S->right;
									 rightRotate(P);
								 }
								 else
								 {
									 S = S->left;
									 leftRotate(P);
								 }
							 }
							 // case 3
							 else if (P->color == 1 && (!S || S->color != 0)
									 && SlColor == 1 && SrColor == 1)
							 {
								 if (S)
									 S->color = 0;
								 if (P->parent)
									 S = (P->parent->right == P)
										 ? P->parent->left : P->parent->right;
								 P = P->parent;
							 }
							 // case 4
							 else if (P->color == 0 && (!S || S->color != 0)
									 && SlColor == 1 && SrColor == 1)
							 {
								 P->color = 1;
								 if (S)
									 S->color = 0;
								 break;
							 }
							 // case 5
							 else if ((!S || S->color != 0)
									 && ((S == P->right && SlColor == 0 && SrColor != 0)
										 || (S == P->left && SrColor == 0 && SlColor != 0)))
							 {
								 if (S && S != _leaf)
									 S->color = 0;
								 if (Sr->color == 0)
								 {
									 Sr->color = 1;
									 leftRotate(S);
								 }
								 else
								 {
									 Sl->color = 1;
									 rightRotate(S);
								 }
								 if (S && S != _leaf)
									 S = S->parent;
							 }
							 // case 6
							 else
							 {
								 if (S == P->left)
								 {
									 Sl->color = 1;
									 rightRotate(P);
								 }
								 else
								 {
									 Sr->color = 1;
									 leftRotate(P);
								 }
								 break;
							 }
						 }
					 }

					 void deleteNode(Node *N)
					 {
						 Node* P;
						 Node* S;

						 _size--;
						 if (N->right && N->left
								 && N->right != _leaf && N->left != _leaf)
							 swapVal(N, getMinimum(N->right));
						 P = N->parent;
						 if (P)
							 S = (P->left == N) ? P->right : P->left;
						 if (N->right && N->right != _leaf)
						 {
							 swapVal(N, N->right);
							 N->parent->right = NULL;
						 }
						 else if (N->left && N->left != _leaf)
						 {
							 swapVal(N, N->left);
							 N->parent->left = NULL;
						 }
						 else
						 {
							 if (N == _root)
							 {
								 _root = NULL;
								 _leaf->right = NULL;
								 _leaf->left = NULL;
							 }
							 else
							 {
								 if (N->parent->right == N)
									 N->parent->right = NULL;
								 else
									 N->parent->left = NULL;
							 }
						 }
						 if (N->color == 1 && _root)
							 RBT_delete(P, S);
						 if (_root)
						 {
							 while (_root->parent)
								 _root = _root->parent;
							 Node *min = getMinimum(_root);
							 Node *max = getMaximum(_root);
							 min->left = _leaf;
							 max->right = _leaf;
							 _leaf->right = min;
							 _leaf->left = max;
						 }
						 _alloc.destroy(static_cast<value_type*>(N->val));
						 _alloc.deallocate(static_cast<value_type*>(N->val), 1);
						 _nodeAlloc.destroy(N);
						 _nodeAlloc.deallocate(N, 1);
					 }

					 // NODE INSERTION
					 // classic BST insert
					 Node*	tree_insert(Node* root, Node* prev,
							 pair<const Key, T> val)
					 {
						 if (!root || root == _leaf)
						 {
							 root = _nodeAlloc.allocate(1);
							 _nodeAlloc.construct(root, Node());
							 root->val = _alloc.allocate(1);
							 _alloc.construct(static_cast<value_type*>
									 (root->val), val);
							 root->parent = prev;
							 if (!_root)
								 _root = root;
						 }
						 else if (!_comp(val.first, static_cast<value_type*>
									 (root->val)->first))
							 root->right = tree_insert(root->right, root, val);
						 else if (_comp(val.first, static_cast<value_type*>
									 (root->val)->first))
							 root->left = tree_insert(root->left, root, val);
						 return (root);
					 }

					 //source
					 //https://en.wikipedia.org/wiki/Red%E2%80%93black_tree#Insertion
					 void	RBT_fixInsert(Node* N)
					 {
						 Node* P = N->parent; //parent
						 Node* G; //grandparent
						 Node* U; // uncle

						 while (P)
						 {
							 if (P->color == 1)
								 return;
							 if ((G = P->parent) == NULL)
							 {
								 P->color = 1;
								 return;
							 }
							 U = (G->right == P) ? G->left : G->right;
							 if (!U || U->color > 0)
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
								 return;
							 }
							 P->color = 1;
							 U->color = 1;
							 G->color = 0;
							 N = G;
							 P = N->parent;
						 }
						 _root->color = 1;
					 }

					 void insertNode(const pair<const Key, T>& val)
					 {
						 _size++;
						 tree_insert(_root, NULL, val);
						 if (_size > 1)
							 RBT_fixInsert(searchTree(_root, val.first));
						 while (_root && _root->parent)
							 _root = _root->parent;
						 Node *min = getMinimum(_root);
						 Node *max = getMaximum(_root);
						 min->left = _leaf;
						 max->right = _leaf;
						 _leaf->right = min;
						 _leaf->left = max;
					 }

				 public:
					 // MEMBER TYPES
					 //		BASIC
					 typedef Key
						 key_type;
					 typedef T
						 mapped_type;
					 typedef pair<const key_type, mapped_type>
						 value_type;
					 typedef Compare
						 key_compare;
					 typedef Alloc
						 allocator_type;
					 typedef typename allocator_type::reference
						 reference;
					 typedef typename allocator_type::const_reference
						 const_reference;
					 typedef typename allocator_type::pointer
						 pointer;
					 typedef typename allocator_type::const_pointer
						 const_pointer;
					 //		ITERATORS
					 typedef mapIterator<value_type>
						 iterator;
					 typedef mapIterator<const value_type>
						 const_iterator;
					 typedef reverse_mapIterator<value_type>
						 reverse_iterator;
					 typedef reverse_mapIterator<const value_type>
						 const_reverse_iterator;
					 typedef std::ptrdiff_t
						 difference_type;
					 typedef std::size_t
						 size_type;

					 class value_compare
					 {
						 friend class map;
						 protected:
						 Compare comp;
						 value_compare (Compare c) : comp(c) {}
						 public:
						 value_compare() {}
						 value_compare(const value_compare& vc) {(void)vc;}
						 value_compare& operator = (const value_compare& vc)
						 {
							 (void)vc;
							 return *this;
						 }
						 ~value_compare() {}
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
						 _nodeAlloc.destroy(_leaf);
						 _nodeAlloc.deallocate(_leaf, 1);
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
						 if (!_size)
							 return (end());
						 return (*_leaf->right);
					 }

					 const_iterator begin() const
					 {
						 if (!_size)
							 return (end());
						 return (*_leaf->right);
					 }

					 iterator end()
					 {
						 return (*_leaf);
					 }

					 const_iterator end() const
					 {
						 return (*_leaf);
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
						 return (_nodeAlloc.max_size());
					 }

					 // ELEMENT ACCESS
					 mapped_type& operator[] (const key_type& k)
					 {
						 return ((insert(ft::make_pair(k, mapped_type())).first)
								 ->second);
					 }

					 // MODIFIERS
					 pair<iterator,bool> insert (const value_type& val)
					 {
						 iterator	inserted_here;
						 bool		is_inserted;

						 inserted_here = find(val.first);
						 if (inserted_here == end())
						 {
							 insertNode(val);
							 is_inserted = true;
							 inserted_here = find(val.first);
						 }
						 else
							 is_inserted = false;
						 return (ft::make_pair(inserted_here, is_inserted));
					 }

					 iterator insert (iterator position, const value_type& val)
					 {
						 Node*	N;

						 if (position != end() && position->first < val.first)
						 {
							 while (position != end()
									 && position->first < val.first)
								 position++;
						 }
						 else if (position != end()
								 && position->first > val.first)
						 {
							 while (position != end()
									 && position->first > val.first)
								 position--;
						 }
						 if (position == end() || position->first != val.first)
						 {
							 insertNode(val);
							 N = searchTree(_root, val.first);
							 return (*N);
						 }
						 else
							 return (position);
					 }

					 template <class InputIterator>
						 void insert (InputIterator first, InputIterator last)
						 {
							 for (InputIterator it = first; it != last; ++it)
								 insert(*it);
						 }

					 void erase (iterator position)
					 {
						 deleteNode(searchTree(_root, position->first));
					 }

					 size_type erase (const key_type& k)
					 {
						 iterator	toDel = find(k);

						 if (toDel == end())
							 return (0);
						 erase(toDel);
						 return (1);
					 }

					 void erase (iterator first, iterator last)
					 {
						 iterator prev = first++;

						 while (prev != last)
						 {
							 deleteNode(searchTree(_root, prev->first));
							 prev = first++;
						 }
					 }

					 void swap (map& x)
					 {

						 typename Alloc::template rebind<Node >::other
							 nodeAlloc_tmp = _nodeAlloc;
						 Alloc		alloc_tmp = _alloc;
						 Compare	comp_tmp = _comp;
						 size_type	size_tmp = _size;
						 Node*		root_tmp = _root;
						 Node*		leaf_tmp = _leaf;

						 _alloc = x._alloc;
						 _comp = x._comp;
						 _size = x._size;
						 _root = x._root;
						 _leaf = x._leaf;

						 x._alloc = alloc_tmp;
						 x._comp = comp_tmp;
						 x._size = size_tmp;
						 x._root = root_tmp;
						 x._leaf = leaf_tmp;
					 }

					 void clear()
					 {
						 clearNode(_root);
						 _size = 0;
						 _root = NULL;
					 }

					 // OBSERVERS
					 key_compare key_comp() const
					 {
						 return (_comp);
					 }

					 value_compare value_comp() const
					 {
						 return (value_compare());
					 }

					 // OPERATIONS
					 iterator find (const key_type& k)
					 {
						 Node*	ret;

						 ret = searchTree(_root, k);
						 if (!ret)
							 return (end());
						 return (iterator(*ret));
					 }

					 const_iterator find (const key_type& k) const
					 {
						 Node*	ret;

						 ret = searchTree(_root, k);
						 if (!ret)
							 return (end());
						 return (const_iterator(*ret));
					 }

					 size_type count (const key_type& k) const
					 {
						 if (find(k) != end())
							 return (1);
						 return (0);
					 }

					 iterator lower_bound (const key_type& k)
					 {
						 iterator	ret = begin();

						 while (ret != end() && _comp(ret->first, k))
							 ret++;
						 return (ret);
					 }

					 const_iterator lower_bound (const key_type& k) const
					 {
						 const_iterator	ret = begin();

						 while (ret != end() && _comp(ret->first, k))
							 ret++;
						 return (ret);
					 }

					 iterator upper_bound (const key_type& k)
					 {
						 iterator ret = lower_bound(k);
						 if (ret == end()
								 || (_comp(k, ret->first)
									 && !_comp(ret->first, k)))
							 return (ret);
						 ret++;
						 return (ret);
					 }

					 const_iterator upper_bound (const key_type& k) const
					 {
						 const_iterator ret = lower_bound(k);
						 if (ret == end()
								 || (_comp(k, ret->first)
									 && !_comp(ret->first, k)))
							 return (ret);
						 ret++;
						 return (ret);
					 }

					 pair<const_iterator,const_iterator> equal_range
						 (const key_type& k) const
						 {
							 return(ft::make_pair(lower_bound(k), upper_bound(k)));
						 }

					 pair<iterator,iterator>	equal_range (const key_type& k)
					 {
						 return(ft::make_pair(lower_bound(k), upper_bound(k)));
					 }

					 // ALLOCATOR
					 allocator_type getallocator() const
					 {
						 return (_alloc);
					 }

			 };

	template< class Key, class T, class Compare, class Alloc >
		bool operator==( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs )
		{
			if (lhs.size() != rhs.size())
				return (0);
			mapIterator<const pair<const Key, T> > left(lhs.begin());
			mapIterator<const pair<const Key, T> > right(rhs.begin());

			while (left != lhs.end() && *left == *right)
			{
				left++;
				right++;
			}
			if (left == lhs.end())
				return (1);
			return (0);
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator!=( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs )
		{
			return (!(lhs == rhs));
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator<( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs )
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
						rhs.begin(), rhs.end()));
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator<=( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs )
		{
			return (lhs < rhs || lhs == rhs);
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator>( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs )
		{
			return (!(lhs <= rhs));
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator>=( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs )
		{
			return (lhs > rhs || lhs == rhs);
		}
}
