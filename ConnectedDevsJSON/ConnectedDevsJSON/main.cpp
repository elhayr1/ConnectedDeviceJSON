#include "devices_tree.h"


int main()
{
	DevicesTree tree;
	tree.feedTree();
	tree.printTree(tree.root());
	tree.printJSONToConsole(NULL);
	
	return 0;
}