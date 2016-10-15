#include "devices_tree.h"
#include "json.hpp"

// for convenience
using json = nlohmann::json;

int main()
{
	DevicesTree tree;
	tree.feedTree();
	tree.printTree(tree.root());
	tree.printJSONToConsole();
	json j;
	j["pi"] = "here";
	std::cout << j.dump(4) << std::endl;
	return 0;
}