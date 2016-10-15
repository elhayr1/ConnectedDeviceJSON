#ifndef DEVICES_TREE_H
#define DEVICES_TREE_H

#include <algorithm>
#include <vector>
//#include "json.hpp"

// for convenience
//using json = nlohmann::json;
#include "devices_parser.h"
#include "device_node.h"



class DevicesTree
{
public:
	DevicesTree();
	~DevicesTree();
	void feedTree();
	void printTree(DeviceNode *node);
	void printNode(DeviceNode *node);
	void printJSONToConsole();
	bool printJSONToFile(char* filePath);
	DeviceNode* root();
	void addNodePath(char* description,
					size_t descSize, 
					char* path, 
					size_t pathSize);

private:
	DeviceNode *_root;
	DevicesParser _devParser;

};

#endif