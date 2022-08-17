#pragma  once
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
					clearNode(_root);
				}


				void	clearNode(node_type* node)
				{
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
					node_type* tmp = new node_type;

					tmp->val = val;
					tmp->parent = parent;
					tmp->left = NULL;
					tmp->right = NULL;
					tmp->color = 0;
					*node = tmp;
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
					else
						throw std::invalid_argument("BST: Duplicate key: " +
								val.first);
					return (root);
				}
				//source
				//https://en.wikipedia.org/wiki/Red%E2%80%93black_tree#Insertion
				// https://course.ccs.neu.edu/cs5010f17/Inheritance
				// /jfp99redblack.pdf
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
							bool dir = (N == P->right);
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

				void insertNode(value_type val)
				{
					node_type* newNode = tree_insert(_root, NULL, val);
					_size++;
					RBT_fixInsert(searchTree(_root, val.first));
				}

				node_type* getMinimum(node_type* N)
				{
					while (N->left)
						N = N->left;
					return (N);
				}

				node_type* getMaximum(node_type* N)
				{
					while (N->right)
						N = N->right;
					return (N);
				}

				void swapVal(node_type* n1, node_type* n2)
				{
					value_type tmp = n1->val;

					n1->val = n2->val;
					n2->val = tmp;
				}

				void moveUp(node_type* n, node_type* nchild)
				{
					nchild->color = 1;
					if (!n->parent)
						_root = nchild;
					else if (n->parent->right == n)
						n->parent->right = nchild;
					else
						n->parent->left = nchild;

				}

				void RBT_delete(node_type* P, node_type* S)
				{
					// case 1
					while (P)
					{
						node_type* Sl = S->left;
						node_type* Sr = S->right;
						// case 2
						if (P->color == 1 && S->color == 0
								&& (!Sl || Sl->color == 1)
								&& (!Sr || Sr->color == 1))
						{
							P->color = 0;
							S->color = 1;
							if (S == P->left)
							{
								S = S->left;
								leftRotate(P);
							}
							else
							{
								S = S->right;
								rightRotate(P);
							}
						}
						// case 3
						else if (P->color == 1 && S->color == 1
								&& (!Sl || Sl->color == 1)
								&& (!Sr || Sr->color == 1))
						{
							S->color = 0;
							if (P->parent)
								S = (P->parent->right == P) ? P->parent->left :
									P->parent->right;
							P = P->parent;
						}
						// case 4
						else if (P->color == 0 && S->color == 1
								&& (!Sl || Sl->color == 1)
								&& (!Sr || Sr->color == 1))
						{
							P->color = 1;
							S->color = 0;
							break;
						}
						// case 5
						else if (P->color == 1 && S->color == 2
								&& (((!Sl || Sl->color == 1)
										&& (Sr && Sr->color == 0))
									|| ((!Sr || Sr->color == 1)
										&& (Sl && Sl->color == 0))
									|| (Sr->color + Sl->color == 1)))
						{
							S->color = 0;
							if (Sr->color = 0)
							{
								Sr->color = 1;
								rightRotate(S);
								S = Sr;
							}
							else
							{
								Sl->color = 1;
								leftRotate(S);
								S = Sl;
							}
						}
						// case 6
						else;
						{
							if (S == P->left)
							{
								Sl->color = 1;
								leftRotate(P);
							}
							else
							{
								Sr->color = 1;
								rightRotate(P);
							}
							break;
						}
					}
				}

				void deleteNode(Key key)
				{
					std::size_t nCol;
					node_type* N = searchTree(_root, key);
					node_type* child;
					node_type* P;
					node_type* S;

					if (!N)
						return ;
					// Reorder if N has two childs
					if (N->right && N->left)
					{
						swapVal(N, getMinimum(N->right));
						N = getMinimum(N->right);
					}
					nCol = N->color;
					P = N->parent;
					S = (P->left == N) ? P->right : P->left;
					if (N->right)
					{
						swapVal(N, N->right);
						N->right = NULL;
					}
					else if (N->left)
					{
						swapVal(N, N->left);
						N->left = NULL;
					}
					else
					{
						if (N == _root)
						{
							_root = NULL;
							return;
						}
						else
						{
							if (N->parent->right == N)
								N->parent->right = NULL;
							else
								N->parent->left = NULL;
						}
					}
					if (nCol == 0 && _root)
						RBT_delete(P, S);
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
