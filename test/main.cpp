#include "rbt.hpp"
#include <utility>
#include <iostream>
#include <string>
#include <stdlib.h>

#define COUNT 2

void print2DUtil(ft::Node<std::pair<int, int> > *root, int space)
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
		std::cout << (root->color ? "\033[1;40m" : "\033[1;41m") <<root->val.first << "\033[0m"<< "parent: "
		<< ((root->parent != NULL) ? root->parent->val.first : -1) << std::endl;

	print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(ft::Node<std::pair<int, int> > *root)
{
	// Pass initial space count as 0
	std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
	print2DUtil(root, 0);
	std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
}

int main ( void )
{
	ft::redBlackTree<int, int> tr;

	int i = 0;

	   for (std::string line; std::getline(std::cin, line);) {
	   try
	   {
	   tr.insertNode(std::make_pair(atoi(line.c_str()), i));
	   }
	   catch (const std::invalid_argument& e)
	   {
	   std::cout << e.what() << std::endl;
	   }
	   std::cout << tr.getRoot()->val.first << " - " << tr.getSize() << std::endl;
	   print2D(tr.getRoot());
	   i++;
	   }
	return 0;

}
