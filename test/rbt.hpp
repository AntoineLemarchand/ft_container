#pragma once
#include <utility>
#include <stdexcept>
#include <iostream>

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

			Node(Pair& vl)
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
				std::allocator<Node<std::pair<Key, T> > >	_alloc;
				Node<std::pair<Key, T> >*					_root;
				std::size_t									_size;
			public:
				typedef	std::pair<Key, T> value_type;
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
					delNode(_root);
				}


				void	delNode(node_type* node)
				{
					if (node && node->left)
						delNode(node->left);
					if (node && node->right)
						delNode(node->right);
					if (node)
					{
						_alloc.destroy(node);
						_alloc.deallocate(node, 1);
					}
				}

				void	leftRotate(node_type* x)
				{
				}

				void	rightRotate(node_type* y)
				{
					node_type* x = y->left;
					node_type* T2 = x->right;

					x->right = y;
					y->left = T2;
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
					{
						root->right = tree_insert(root->right, root, val);
						return (root->right);
					}
					else if (val.first < root->val.first)
					{
						root->left = tree_insert(root->left, root, val);
						return (root->left);
					}
					else
						throw std::invalid_argument("BST: Duplicate key: " + val.first);
					return (root);
				}

				// red black tree twist after insert
				void	RBT_fixInsert(node_type* newNode)
				{
					while (newNode->parent != NULL && newNode->parent != _root
							&& newNode->parent->color != 1)
					{
						node_type*	uncle = (newNode->parent == newNode->parent->parent->left) ? newNode->parent->parent->right : newNode->parent->parent->left;
						bool	parentSide = (newNode->parent->parent->right == newNode->parent);
						bool	newNodeSide = (newNode->parent->right == newNode);

						if (uncle && uncle->color == 0)
							newNode = newNode->parent->parent;
						else
						{
							if (parentSide != newNodeSide)
							{
								if (newNodeSide == 1)
									rightRotate(newNode->parent);
								else
									leftRotate(newNode->parent);
								newNode = newNode->parent;
							}
							if (parentSide == 1)
								rightRotate(newNode->parent->parent);
							else
								leftRotate(newNode->parent->parent);

						}
					}
					_root->color = 1;
				}

				void insertNode(value_type val)
				{
					node_type* newNode = tree_insert(_root, NULL, val);
					_size++;
					RBT_fixInsert(newNode);
				}

				node_type* getRoot( void )
				{
					return (_root);
				}

				std::size_t getSize( void )
				{
					return (_size);
				}
		};
}
