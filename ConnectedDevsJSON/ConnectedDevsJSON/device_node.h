#ifndef DEVICE_NODE_H
#define DEVICE_NODE_H

#include <vector>
#include <string>
class DeviceNode
{
public:
	DeviceNode();
	DeviceNode(DeviceNode parent,  char* devInstId, char* description);
	DeviceNode* getParent();
	DeviceNode* getSuccessor(char* devInstId);
	void setParent(DeviceNode parent);
	void setDevInstId(char* instId);
	void setDescription(char* desc);
	void addSuccessor(DeviceNode child);

private:
	DeviceNode *_parent;
	char *_devInstId, *_description;
	std::vector<DeviceNode*> _successors;


};

#endif