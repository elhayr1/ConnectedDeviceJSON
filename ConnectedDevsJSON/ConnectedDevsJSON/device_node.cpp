#include "device_node.h"

DeviceNode::DeviceNode(
						DeviceNode *parent,
						char* devInstId,
						size_t devInstSize,
						char* description,
						size_t descSize,
						bool pathNode
						)
{
	_parent = parent;
	_devInstId = devInstId;
	_description = description;
	_pathNode = pathNode;
	_descSize = descSize;
	_devInstSize = devInstSize;
}

DeviceNode::DeviceNode() 
{
	_parent = NULL;
	_pathNode = true;
	_descSize = _devInstSize = 0;
}


DeviceNode* DeviceNode::getSuccessor(char* path, size_t pathSize)
{
	bool found = true;
	for (DeviceNode* devNode : _successors)
	{
		if (pathSize == devNode->devInstLen())
		{
			for (int i = 0; i < pathSize && found == true; i++)
			{
				if (path[i] != devNode->getDevInstId()[i])
					found = false;
			}
			if (found)
				return devNode;
			else
				found = true;
		}
	}
	return NULL;
}

void DeviceNode::addSuccessor(DeviceNode *child) {_successors.push_back(child);}
void DeviceNode::rmSuccessor(int index) { _successors.erase(_successors.begin()+index); }
DeviceNode* DeviceNode::getParent() { return _parent;}
void DeviceNode::setParent(DeviceNode *parent) {_parent = parent;}
void DeviceNode::setDevInstId(char *instId) { _devInstId = instId; }
void DeviceNode::setDescription(char *desc) { _description = desc; }
bool DeviceNode::isPathNode() { return _pathNode; }
size_t DeviceNode::devInstLen() { return _devInstSize; }
size_t DeviceNode::descLen() { return _descSize; }
char* DeviceNode::getDevInstId() { return _devInstId; }
char* DeviceNode::getDescription() { return _description; }
int DeviceNode::successorsNum() { return _successors.size(); }
DeviceNode* DeviceNode::getSuccessor(int index) { return _successors[index]; }