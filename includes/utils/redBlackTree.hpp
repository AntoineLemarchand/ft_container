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
		};

	template<class Key, class T, class comp>
		class redBlackTree
		{
			private:
				std::allocator<Node<pair<Key, T> > >	_alloc;
				Node<pair<Key, T> >*					_root;
			public:
				typedef	pair<Key, T> value_type;
				typedef	Node<value_type> node_type;

				redBlackTree() { _root = NULL; }
				redBlackTree( const redBlackTree& tr) { *this = tr; }
				redBlackTree& operator= ( const redBlackTree& tr)
				{
					if (this != &tr)
						_root = tr.getRoot();
					return (*this);
				}

				// x = node to put left of y
				// y = node to put on top
				// ALGORITHM
				// x right part become y left part
				// the new parent of y is x old parent (back up)
				// if x was root, update _root
				// put x on y left
				void	leftRotate(node_type* x)
				{
					node_type* y = x->right;

					x->right = y->left;
					if (y->left != NULL)
						y->left->parent = x;
					y->parent = x->parent;
					if (x->parent == NULL)
						_root = y;
					else
						if (x == (x->parent)->left)
							x->parent->left = y;
						else
							x->parent->right = y;
					y->left = x;
					x->parent = y;
				}

				// y = node to put right of x
				// x = node to put on top
				// ALGORITHM
				// y left part become x right part
				// the new parent of x is y old parent (back up)
				// if y was root, update _root
				// put y on x right
				void	rightRotate(node_type* y)
				{
					node_type* x = y->left;

					y->left = x->right;
					if (x->right != NULL)
						x->right->parent = y;
					x->parent = y->parent;
					if (y->parent == NULL)
						_root = x;
					else
						if (y == y->parent->right)
							y->parent->right = x;
						else
							y->parent->left = x;
					x->right = y;
					y->parent = x;
				}

				void	initNode(node_type* node, node_type* parent,
						value_type val)
				{
					node_type tmp;
					tmp.val = val;
					tmp.parent = parent;
					tmp.left = NULL;
					tmp.right = NULL;
					tmp.color = 0;
					node = _alloc.allocate(1);
					_alloc.construct(node, tmp);
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
						initNode(root, prev,val);
						return (root);
					}
					else if (val > root->val)
						root->right = tree_insert(root->right, root, val);
					else if (val < root->val)
						root->left = tree_insert(root->left, root, val);
					else
						throw std::invalid_argument("BST: Duplicate key: " + val->first);
					return (root);
				}

				// red black tree twist after insert
				void	RBT_fixInsert(node_type* newNode)
				{
					node_type* parent = newNode->parent;

					if (newNode == _root || parent == _root)
					{
						_root->color = 1;
						return;
					}
					if (parent->color == 1)
						return;
					node_type* gParent = parent->parent;
					node_type* uncle = (newNode == parent->right) ?
						gParent->left : gParent->right;
					if (uncle != NULL && uncle->color == 0)
					{
						gParent->color = 0;
						parent->color = 1;
						uncle->color = 1;
						fix_redBlackTree(gParent);
					}
					else if (parent == gParent->left)
					{
						if (newNode == parent->right)
						{
							leftRotate(parent);
							parent = newNode;
						}
						rightRotate(gParent);
						parent->color = 1;
						gParent->color = 0;
					}
					else
					{
						if (newNode == parent->left)
						{
							rightRotate(parent);
							parent = newNode;
						}
						leftRotate(gParent);
						parent->color = 1;
						gParent->color = 0;
					}
				}

				void insertNode(value_type val)
				{
					fix_redBlackTree(tree_insert(_root, NULL, val));
				}
		};
}
