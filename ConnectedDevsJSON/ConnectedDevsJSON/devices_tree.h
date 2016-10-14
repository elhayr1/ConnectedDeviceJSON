#ifndef DEVICES_TREE_H
#define DEVICES_TREE_H

#include "devices_parser.h"
#include "device_node.h"

class DevicesTree
{
public:
	DevicesTree();
	~DevicesTree();
	void feedTree();
	void printToConsole();
	bool printToFile(char* filePath);
	DeviceNode root();
	void addNode(DeviceNode devNode);

private:
	DeviceNode *_root;
	DevicesParser _devParser;

};

#endif