#pragma once
#include "pair.hpp"
#include <stdexcept>

namespace ft
{
	template<class Pair>
		struct Node
		{
			struct Node*	parent;
			struct Node*	left;
			struct Node*	right;
			Pair			val;
			bool			color;

			Node()
			{
				parent = NULL;
				left = NULL;
				right = NULL;
				color = 0;
			}

			Node(const Pair& vl)
			{
				parent = NULL;
				left = NULL;
				right = NULL;
				color = 0;
				val = vl;
			}
		};

	template<class Key, class T>
		class redBlackTree
		{
			private:
				std::allocator<Node<pair<Key, T> > >	_alloc;
				Node<pair<Key, T> >*					_root;
				std::size_t									_size;
			public:
				typedef	pair<Key, T> value_type;
				typedef	Node<value_type> node_type;

				redBlackTree()
				{
					_root = NULL;
					_size = 0;
				}

				redBlackTree( const redBlackTree& tr) { *this = tr; }

				redBlackTree& operator= ( const redBlackTree& tr)
				{
					if (this != &tr)
					{
						_root = tr.getRoot();
						_size = tr.getSize();
					}
					return (*this);
				}

				~redBlackTree()
				{
					clearNode(_root);
				}

				void	clearNode(node_type* node)
				{
					_size--;
					if (node && node->left)
						clearNode(node->left);
					if (node && node->right)
						clearNode(node->right);
					if (node)
					{
						_alloc.destroy(node);
						_alloc.deallocate(node, 1);
					}
				}

				void	leftRotate(node_type* l)
				{
					node_type*	r;

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

				void	rightRotate(node_type* r)
				{
					node_type*	l;

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

				void	initNode(node_type** node, node_type* parent,
						value_type val)
				{
					node_type tmp;

					tmp.val = val;
					tmp.parent = parent;
					tmp.left = NULL;
					tmp.right = NULL;
					tmp.color = 0;
					*node = _alloc.allocate(1);
					_alloc.construct(*node, tmp);
				}

				node_type*	searchTree(node_type* root, Key key)
				{
					if (root == NULL || root->val.first == key)
						return (root);
					if (root->val.first < key)
						return (searchTree(root->right, key));
					return (searchTree(root->left, key));
				}

				// classic BST insert
				node_type*	tree_insert(node_type* root, node_type* prev,
						value_type val)
				{
					if (!root)
					{
						initNode(&root, prev, val);
						if (_size == 0)
							_root = root;
					}
					else if (val.first > root->val.first)
						root->right = tree_insert(root->right, root, val);
					else if (val.first < root->val.first)
						root->left = tree_insert(root->left, root, val);
					return (root);
				}
//source
//https://en.wikipedia.org/wiki/Red%E2%80%93black_tree#Insertion
				void	RBT_fixInsert(node_type* N)
				{
					node_type* P = N->parent; //parent
					node_type* G; //grandparent
					node_type* U; // uncle

					_root->color = 1;
					while (P)
					{
						if (!P || P->color == 1)
							return;
						if ((G = P->parent) == NULL)
						{
							P->color = 1;
							return;
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
							return;
						}
						P->color = 1;
						U->color = 1;
						G->color = 0;
						N = G;
						P = N->parent;
					}
				}

				void	RBT_delNode(node_type* N)
				{
					node_type* P = N->parent; // parent
					node_type* S; // sibling
					node_type* C; // close nephew
					node_type* D; // distant nephew
				}

				void insertNode(const value_type& val)
				{
					tree_insert(_root, NULL, val);
					_size++;
					RBT_fixInsert(searchTree(_root, val.first));
				}

				void shiftNode(node_type* to, node_type* from)
				{
					if (from->parent)
					{
						if (from->parent->right == from)
							from->parent->right = NULL;
						else
							from->parent->left = NULL;
					}
					to->val = from->val;
					_alloc.destroy(from);
					_alloc.deallocate(from, 1);
				}

				node_type* getMinimum(node_type* N)
				{
					while (N->left)
						N = N->left;
					return (N);
				}

//using
//https://medium.com/analytics-vidhya/deletion-in-red-black-rb-tree-92301e1474ea
				void deleteNode(node_type* N)
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
						_alloc.destroy(N);
						_alloc.deallocate(N, 1);
					}
				}

				node_type* getRoot( void ) const
				{
					return (_root);
				}

				std::size_t getSize( void ) const
				{
					return (_size);
				}
		};
}
