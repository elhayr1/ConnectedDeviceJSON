#include "devices_tree.h"

DevicesTree::DevicesTree()
{
	_root = new DeviceNode(NULL, "TREE ROOT", 9, NULL, 4, true);
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
		// Insert error handling here.
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
		
		//_devParser.getDevInfo(hDevInfo, DeviceInfoData, L"Friendly name :", SPDRP_FRIENDLYNAME);
		
		//if (desc !=NULL)
		//	std::cout << "HERE! FREINDLY: "<< desc << "\n\n";

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
			{
				// Change the buffer size.
				// Double the size to avoid problems on
				// W2k MBCS systems per KB 888609.
				buffer = (LPTSTR)LocalAlloc(LPTR, buffersize * 2);
			}
			else
			{
				wprintf(L"error: could not get device instance id (0x%x)\n", GetLastError());
				return;
			}
		}

		
		if (buffer)
		{
			//wprintf(L"\tDeviceInstanceId : %s\n", buffer);

			devInstSize = _devParser.lptstr2str(buffer, devInstId);

			//std::cout << "devInstId: " << devInstId << "\n";
		}

		//_devParser.getDevInfo(hDevInfo, DeviceInfoData , SPDRP_CLASS);
		//print_property(hDevInfo, DeviceInfoData, L"\tClass GUID :", SPDRP_CLASSGUID);


		addNodePath(desc, descSize, devInstId, devInstSize);

	}


	if (NO_ERROR != GetLastError() && ERROR_NO_MORE_ITEMS != GetLastError())
	{
		// Insert error handling here.
		return;
	}

	// Cleanup
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
				existedSucc == NULL) //node not exist
			{
				//create device node and position in tree
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
	//add last node HERE
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
		std::string father((node->getParent())->getDevInstId(), node->getParent()->devInstLen());
		std::cout << "Father: " << father << "\n";
	}
	std::cout << "-------------------------" << "\n\n";
}

void DevicesTree::printJSONToConsole(DeviceNode *node)
{
	char *a = new char[100];
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																		}  ";
	const wchar_t* EXAMPLE = L"\
							  { \
							  	\"string_name\" : \"string\tvalue and a \\\"quote\\\" and a unicode char \\u00BE and a c:\\\\path\\\\ or a \\/unix\\/path\\/ :D\", \
									\"bool_name\" : true, \
										\"bool_second\" : FaLsE, \
											\"null_name\" : nULl, \
												\"negative\" : -34.276, \
													\"sub_object\" : { \
																			\"foo\" : \"abc\", \
																									 \"bar\" : 1.35e2, \
																									 						 \"blah\" : { \"a\" : \"A\", \"b\" : \"B\", \"c\" : \"C\" } \
																															 					}, \
																																					\"array_letters\" : [ \"a\", \"b\", \"c\", [ 1, 2, 3  ]  ] \
																																					}    ";
	JSONValue *value = JSON::Parse(EXAMPLE);

	std::wcout << value->Stringify(true).c_str();


	
	
	//if (node->successorsNum() == 0) //bottom node reached
	//{
	//	printNode(node);
	//	return;
	//}
	//printNode(node);
	//for (int i = 0; i < node->successorsNum(); i++)
	//	printTree(node->getSuccessor(i));
}

DeviceNode* DevicesTree::root() { return _root; }

DevicesTree::~DevicesTree()
{
	//TODO: delete all nodes in tree, 
	//IN every NODE also delete desctiption and device inst ID
	//delete pointer if not null
}