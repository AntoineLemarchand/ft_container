#include "rbt.hpp"
#include <utility>
#include <iostream>
#include <string>
#include <stdlib.h>

#define COUNT 2

void print2DUtil(ft::Node<std::pair<int, std::string> > *root, int space)
{
	// Base case
	if (root == NULL)
		return;

	space += COUNT;

	print2DUtil(root->right, space);

	std::cout<<std::endl;
	for (int i = COUNT; i < space; i++)
		std::cout<<" ";
	if (root->parent)
		std::cout<< (root->parent && root->parent->left == root ? "┗" : "┏");
	std::cout << (root->color ? "\033[1;40m" : "\033[1;41m") <<root->val.first << ":" << root->val.second
		<< "\033[0m";
	std::cout << "[";
	if (root->parent)
		std::cout << " P: " <<  root->parent->val.first;
	if (root->left)
		std::cout << " L: " << root->left->val.first;
	if (root->right)
		std::cout<< " R: " <<root->right->val.first;
	std::cout << " ]" << std::endl;

	print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(ft::Node<std::pair<int, std::string> > *root)
{
	// Pass initial space count as 0
	std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
	print2DUtil(root, 0);
	std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
}

#include <list>
int main ( void )
{
	ft::redBlackTree<int, std::string> tr;

	std::list<std::pair<int, std::string> > lst;
	for (unsigned int i = 0; i < 10; ++i)
		lst.push_back(std::pair<int, std::string>(i, std::string((10 - i), i + 65)));
	for (std::list<std::pair<int, std::string> >::iterator it = lst.begin(); it !=lst.end(); it++)
		tr.insertNode(*it);
	tr.deleteNode(1);

	tr.deleteNode(0);
	tr.deleteNode(10);

	tr.deleteNode(2);
	tr.deleteNode(3);
	tr.deleteNode(4);

	print2D(tr.getRoot());
	tr.deleteNode(7);
	print2D(tr.getRoot());
	tr.deleteNode(8);

	tr.insertNode(std::make_pair(10, "Hello"));
	tr.insertNode(std::make_pair(11, "Hi there"));
	tr.deleteNode(9);
	tr.deleteNode(10);
	tr.deleteNode(11);
	tr.insertNode(std::make_pair(12, "ONE"));
	tr.insertNode(std::make_pair(13, "TWO"));
	tr.insertNode(std::make_pair(14, "THREE"));
	tr.insertNode(std::make_pair(15, "FOUR"));
	tr.deleteNode(5);
	tr.deleteNode(6);
	tr.deleteNode(12);
	tr.deleteNode(13);
	tr.deleteNode(14);
	tr.deleteNode(15);

	/*
	for (std::string line; std::getline(std::cin, line);) {
		if (line[0] == 'd')
			tr.deleteNode(tr.searchTree(tr.getRoot(), atoi(&line[1])));
		else
			tr.insertNode(std::make_pair(atoi(line.c_str()), i));
		print2D(tr.getRoot());
		i++;
	}
	*/
	return 0;
}
