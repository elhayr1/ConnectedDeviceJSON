#ifndef DEVICES_TREE_H
#define DEVICES_TREE_H

#include <algorithm>
#include <vector>
#include "JSON.h"
#include <json.h>
#include "devices_parser.h"
#include "device_node.h"

class DevicesTree
{
public:
	DevicesTree();
	~DevicesTree();
	void feedTree();
	void devicesTreeToJSON(DeviceNode *node, JSONObject& out);
	void printTree(DeviceNode *node);
	void printNode(DeviceNode *node);
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