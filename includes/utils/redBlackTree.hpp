#pragma once

namespace ft
{
	template<class Key, class T>
		struct Node
		{
			struct Node*	parent;
			struct Node*	left;
			struct Node*	right;
			pair<Key, T>	val;
			enum { red, black } color;
		};

	template<class Key, class T, class comp>
		class redBlackTree
		{
			private:
				Node<Key, T>*	_root;

				// x = node to put left of y
				// y = node to put on top
				// ALGORITHM
				// x right part become y left part
				// the new parent of y is x old parent (back up)
				// if x was root, update _root
				// put x on y left
				void	leftRotate(Node* x)
				{
					Node* y = x->right;

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
				void	rightRotate(Node* y)
				{
					Node* x = y->left;

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

			public:
				typedef	typename	pair<Key, T> value_type;

				void	initNode(Node* node, Node* parent, value_type val)
				{
					node->val = val;
					node->parent = parent;
					node->left = NULL;
					node->right = NULL;
					node->color = red;
				}

				Node*	searchTree(Node* root, Key key)
				{
					if (root == NULL || root->val.first == key)
						return (root);
					if (root->val.first < key)
						return (searchTree(root->right, key));
					return (searchTree(root->left, key));
				}

				// classic BST insert
				Node*	tree_insert(Node* root, value_type val)
				{
					if (!root)
					{
						initNode(root, val);
						return (root);
					}
					else if (val > root->val)
						root->right = Insert(root->right, val);
					else 
						root->left = Insert(root->left, val);
					return (root);
				}

				void insertNode(Node* newNode)
				{
					tree_insert(_root, newNode)
					if (newNode == _root)
						newNode->color = 1;
				}
				
				void	deleteNode(int key)
				{
				}
		}
}
