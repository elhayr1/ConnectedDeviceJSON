#ifndef DEVICE_NODE_H
#define DEVICE_NODE_H

#include <vector>
#include <string>

class DeviceNode
{
public:
	DeviceNode();
	DeviceNode(
				DeviceNode *parent,
				char* devInstId,
				size_t devInstSize,
				char* description,
				size_t descSize,
				bool pathNode
				);
	DeviceNode* getParent();
	DeviceNode* getSuccessor(char* path, size_t pathSize);
	DeviceNode* getSuccessor(int index);
	void setParent(DeviceNode* parent);
	void setDevInstId(char* instId);
	void setDescription(char* desc);
	void addSuccessor(DeviceNode *child);
	bool isPathNode();
	size_t devInstLen();
	size_t descLen();
	char* getDevInstId();
	char* getDescription();
	int successorsNum();


private:
	DeviceNode *_parent;
	char *_devInstId, *_description;
	std::vector<DeviceNode*> _successors;
	bool _pathNode;
	size_t _descSize, _devInstSize;
};

#endif