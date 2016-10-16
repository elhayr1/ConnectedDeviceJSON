#ifndef DEVICES_PARSER_H
#define DEVICES_PARSER_H

#include <windows.h>
#include <setupapi.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <tchar.h>
#include <vector>
#pragma comment(lib,"SetupAPI") 

class DevicesParser
{
public:
	DevicesParser(){};
	size_t lptstr2str(LPTSTR tch, char* &pch);
	size_t getDevInfo(
						char * &res,
						__in HDEVINFO hDevInfo,
						__in SP_DEVINFO_DATA DeviceInfoData,
						__in DWORD Property
						);
private:
	


};

#endif