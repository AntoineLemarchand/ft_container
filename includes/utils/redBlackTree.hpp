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
				Node*	tree_insert(Node* root, Node* prev, value_type val)
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
						throw new IllegalArgumentException("BST: Duplicate key: " + val->first);
					return (root);
				}

				// red black tree twist after insert
				void	RBT_fixInsert(Node* newNode)
				{
					Node* parent = newNode->parent;

					if (newNode == _root || parent = _root)
					{
						_root->color = black;
						return;
					}
					if (parent->color == black)
						return;
					Node* gParent = parent->parent;
					Node* uncle = (newNode == parent->right) ?
						gParent->left : gParent->right;
					if (uncle != NULL && uncle->color == red)
					{
						gParent->color = red;
						parent->color = black;
						uncle->color = black;
						fix_redBlackTree(gParent);
					}
					else if (parent == gParent->left)
					{
						if (newnode == parent->right)
						{
							leftRotate(parent);
							parent = newNode;
						}
						rightRotate(gParent);
						parent->color = black;
						gParent->color = red;
					}
					else
					{
						if (newNode == parent->left)
						{
							rightRotate(parent);
							parent = newNode;
						}
						leftRotate(gParent);
						parent->color = black;
						gParent->color = red;
					}
				}

				void insertNode(value_type val)
				{
					fix_redBlackTree(tree_insert(_root, NULL, val));
				}
		}
}
