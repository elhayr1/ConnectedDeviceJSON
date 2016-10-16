#include "devices_tree.h"

DevicesTree::DevicesTree()
{
	_root = new DeviceNode(NULL, "TREE ROOT", 
							9, NULL, 0, true);
}

void DevicesTree::feedTree()
{
	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA DeviceInfoData;
	DWORD i;

	// Create a HDEVINFO with all present devices.
	hDevInfo = SetupDiGetClassDevs(
		NULL,
		0,
		0,
		DIGCF_PRESENT | DIGCF_ALLCLASSES);

	if (INVALID_HANDLE_VALUE == hDevInfo)
	{
		if (DEBUG_MODE) { std::cout << "\nError: invalid devices handle value\n"; }
		return;
	}

	// Enumerate through all devices in Set.
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	for (i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++)
	{
		LPTSTR buffer = NULL;
		DWORD buffersize = 0;

		char *devInstId = NULL;
		size_t devInstSize = 0;

		char *desc = NULL;
		size_t descSize = 0;

		descSize = _devParser.getDevInfo(
										desc,
										hDevInfo, 
										DeviceInfoData, 
										SPDRP_FRIENDLYNAME
										);
		
		while (!SetupDiGetDeviceInstanceId(
											hDevInfo,
											&DeviceInfoData,
											buffer,
											buffersize,
											&buffersize
											))
		{
			if (buffer)
				LocalFree(buffer);

			if (ERROR_INSUFFICIENT_BUFFER == GetLastError())
				buffer = (LPTSTR)LocalAlloc(LPTR, buffersize * 2);
			else
			{
				if (DEBUG_MODE) { wprintf(L"error: could not get device instance id (0x%x)\n", GetLastError()); }
				return;
			}
		}

		if (buffer)
			devInstSize = _devParser.lptstr2str(buffer, devInstId);

		addNodePath(desc, descSize, devInstId, devInstSize);
	}


	if (NO_ERROR != GetLastError() && ERROR_NO_MORE_ITEMS != GetLastError())
		return;

	SetupDiDestroyDeviceInfoList(hDevInfo);
}

void DevicesTree::addNodePath(char* description,
								size_t descSize,
								char* path,
								size_t pathSize)
{
	u_int charCounter = 0;
	u_int prevCharCounter = 0;
	DeviceNode *parent = _root;
	for (u_int i = 0; i < pathSize; i++)
	{
		charCounter++;
		if (path[i] == '\\')
		{	
			charCounter--; //don't count slash

			char *pathChar = new char[charCounter];
			for (u_int i = 0; i < charCounter; i++)
				pathChar[i] = path[i + prevCharCounter];

			DeviceNode *existedSucc = parent->getSuccessor(pathChar, charCounter);
			if (parent->successorsNum() == 0 ||
				existedSucc == NULL) //node doesnt exist in tree 
			{
				//create path node and position it in tree
				DeviceNode *newDevNode = new DeviceNode(
														parent,
														pathChar,
														charCounter,
														NULL, 0,
														true
														);
				parent->addSuccessor(newDevNode);
				parent = newDevNode;
			}
			else
			{
				parent = existedSucc;
				delete pathChar;
			}
			prevCharCounter += charCounter + 1;
			charCounter = 0;
		}
	}
	//add device node to tree
	parent->addSuccessor(new DeviceNode(
										parent, 
										path, pathSize,
										description, descSize, 
										false
										));
}

void DevicesTree::printTree(DeviceNode *node)
{
	if (node->successorsNum() == 0) //bottom node reached
	{
		printNode(node);
		return;
	}
	printNode(node);
	for (int i = 0; i < node->successorsNum(); i++)
		printTree(node->getSuccessor(i));
}

void DevicesTree::printNode(DeviceNode *node)
{
	std::cout << "--------NODE INFO--------" << "\n";
	if (node->isPathNode())
		std::cout << "Path Node\n";
	else
		std::cout << "Device Node\n";
	if (node->getDevInstId() != NULL)
	{
		std::string path(node->getDevInstId(), node->devInstLen());
		std::cout << "Path: " << path << "\n";
	}
	if (node->getDescription() != NULL)
	{
		std::string descp(node->getDescription(), node->descLen());
		std::cout << "Description: " << descp << "\n";
	}
	if (node->getParent() != NULL && node->getParent()->getDevInstId() != NULL)
	{
		std::string parent((node->getParent())->getDevInstId(), node->getParent()->devInstLen());
		std::cout << "Parent: " << parent << "\n";
	}
	std::cout << "-------------------------" << "\n\n";
}

void DevicesTree::devicesTreeToJSON(DeviceNode *node, JSONObject & out)
{	
	//convert string to cont wchar_t*
	std::string strDevId;
	strDevId.append(node->getDevInstId(), node->devInstLen());
	std::wstring convertor = std::wstring(strDevId.begin(), strDevId.end());
	const wchar_t* deviceVal = convertor.c_str();
	
	if (node->successorsNum() == 0) //device node reached
	{
		out[L"Instance ID"] = new JSONValue(deviceVal);
		if (node->getDescription() != NULL)
		{
			std::string strDevDesc;
			strDevId.append(node->getDescription(), node->descLen());
			std::wstring convertor = std::wstring(strDevDesc.begin(), strDevDesc.end());
			const wchar_t* deviceVal = convertor.c_str();
			out[L"Description"] = new JSONValue(deviceVal);
		}
		return;
	}

	//path node reached
	JSONObject subObj;
	if (node->getSuccessor(0)->successorsNum() == 0)
	{
		
		for (int i = 0; i < node->successorsNum(); i++)
			devicesTreeToJSON(node->getSuccessor(i), subObj);

		out[deviceVal] = new JSONValue(subObj);
	}
	else
	{
		for (int i = 0; i < node->successorsNum(); i++)
			devicesTreeToJSON(node->getSuccessor(i), subObj);

		out[deviceVal] = new JSONValue(subObj);
	}  
}

DeviceNode* DevicesTree::root() { return _root; }

void DevicesTree::deleteTree(DeviceNode *node)
{
	if (node->successorsNum() == 0)
	{
		if (node->getDescription() != NULL)
			delete node->getDescription();
		if (node->getDevInstId() != NULL)
			delete node->getDevInstId();
		if (node!=NULL)
			delete node;
		return;
	}

	for (int i = 0; i < node->successorsNum(); i++)
		deleteTree(node->getSuccessor(i));

	if (node->getParent()!=NULL && node->getDevInstId() != NULL)
		delete node->getDevInstId();
	
	if (node != NULL)
		delete node;
}

DevicesTree::~DevicesTree() { deleteTree(_root); }