#include "device_node.h"

DeviceNode::DeviceNode(DeviceNode parent, char* devInstId, char* description)
{
	_parent = &parent;
	_devInstId = devInstId;
	_description = _description;
}

DeviceNode::DeviceNode() {_parent = NULL;}


DeviceNode* DeviceNode::getSuccessor(char* devInstId)
{
	for (DeviceNode* devNode : _successors)
	{
		if (std::strcmp(devNode->_devInstId, devInstId))
			return devNode;
	}
	return NULL;
}

void DeviceNode::addSuccessor(DeviceNode child) {_successors.push_back(&child);}

DeviceNode* DeviceNode::getParent() { return _parent;}

void DeviceNode::setParent(DeviceNode parent) {_parent = &parent;}

void DeviceNode::setDevInstId(char *instId) { _devInstId = instId; }
void DeviceNode::setDescription(char *desc) { _description = desc; }