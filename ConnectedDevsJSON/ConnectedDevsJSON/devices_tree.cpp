#include "devices_tree.h"

DevicesTree::DevicesTree()
{
	_root = NULL;
}

void DevicesTree::feedTree()
{
	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA DeviceInfoData;
	DWORD i;

	// Create a HDEVINFO with all present devices.
	hDevInfo = SetupDiGetClassDevs(
		NULL,
		0, // Enumerator
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

		//_devParser.getDevInfo(hDevInfo, DeviceInfoData, L"Friendly name :", SPDRP_FRIENDLYNAME);
		char *a = _devParser.getDevInfo(hDevInfo, DeviceInfoData, SPDRP_FRIENDLYNAME);
		if (a !=NULL)
			std::cout << "HERE! FREINDLY: "<< a << "\n\n";
		while (!SetupDiGetDeviceInstanceId(
			hDevInfo,
			&DeviceInfoData,
			buffer,
			buffersize,
			&buffersize))
		{
			if (buffer)
			{
				LocalFree(buffer);
			}

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
				break;
			}
		}

		if (buffer)
		{
			wprintf(L"\tDeviceInstanceId : %s\n", buffer);

			char *arr;
			_devParser.lptstr2str(buffer, arr);

			std::cout << "HERE: " << arr << "\n";
		}

		_devParser.getDevInfo(hDevInfo, DeviceInfoData , SPDRP_CLASS);
		//print_property(hDevInfo, DeviceInfoData, L"\tClass GUID :", SPDRP_CLASSGUID);
	}


	if (NO_ERROR != GetLastError() && ERROR_NO_MORE_ITEMS != GetLastError())
	{
		// Insert error handling here.
		return;
	}

	// Cleanup
	SetupDiDestroyDeviceInfoList(hDevInfo);
}

DevicesTree::~DevicesTree()
{
	//TODO: delete all nodes in tree!
}