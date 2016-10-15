#include "devices_parser.h"

size_t DevicesParser::lptstr2str(LPTSTR tch, char* &pch) // or (TCHAR* tch, char* &pch)
{
#ifndef UNICODE
	std::memcpy(pch, tch, strlen(tch) + 1);
#else
	size_t n =
		sizeof(TCHAR) / sizeof(char)* wcsnlen(tch, std::string::npos);
	pch = new char[n + 1];
	std::memcpy(pch, tch, n + 1);
	int len = n - std::count(pch, pch + n, NULL);
	std::remove(pch, pch + n, NULL);
	pch[len] = NULL;
	return len;
#endif
}

size_t DevicesParser::getDevInfo(
	char * &res,
	__in HDEVINFO hDevInfo,
	__in SP_DEVINFO_DATA DeviceInfoData,
	__in DWORD Property
	)
{
	DWORD DataT;
	LPTSTR buffer = NULL;
	DWORD buffersize = 0;

	// 
	while (!SetupDiGetDeviceRegistryProperty(
		hDevInfo,
		&DeviceInfoData,
		Property,
		&DataT,
		(PBYTE)buffer,
		buffersize,
		&buffersize))
	{
		if (ERROR_INSUFFICIENT_BUFFER == GetLastError())
		{
			// Change the buffer size.
			if (buffer)
			{
				LocalFree(buffer);
			}
			// Double the size to avoid problems on 
			// W2k MBCS systems per KB 888609. 
			buffer = (LPTSTR)LocalAlloc(LPTR, buffersize * 2);
		}
		else
		{
			break;
		}
	}

	//wprintf(L"%s %s\n", Label, buffer);
	
	res = NULL;
	size_t resSize = 0;

	if (buffer)
	{
		resSize = lptstr2str(buffer, res);
		LocalFree(buffer);
	}
	return resSize;
}

