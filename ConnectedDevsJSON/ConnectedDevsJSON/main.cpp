#include "devices_tree.h"

int main()
{
	DevicesTree tree;
	tree.feedTree();
	tree.printTree(tree.root());
	return 0;
}