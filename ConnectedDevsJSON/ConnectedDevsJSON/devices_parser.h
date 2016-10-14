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
	void lptstr2str(LPTSTR tch, char* &pch);
	void getConnectedDevice(
		__in HDEVINFO hDevInfo,
		__in SP_DEVINFO_DATA DeviceInfoData,
		__in PCWSTR Label,
		__in DWORD Property
		);
private:



};

#endif