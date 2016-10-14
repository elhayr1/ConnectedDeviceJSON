#ifndef DEVICE_NODE_H
#define DEVICE_NODE_H

#include <vector>

class DeviceNode
{
public:
	DeviceNode(){};
	DeviceNode(char* devInstId, char* description);
	DeviceNode getParent();
	DeviceNode getSuccessor();
	void setParent(DeviceNode parent);
	void addSuccessor(char* devInstId);
	void rmSuccessor(char* devInstId);

private:
	char* _devInstId, _description;
	std::vector<DeviceNode> _successors;


};

#endif