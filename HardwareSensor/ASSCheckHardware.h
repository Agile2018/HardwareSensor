#ifndef ASSCheckHardware_h
#define ASSCheckHardware_h


#include "windows.h"
#include "ASSFaceCodes.h"
#include "Format.h"
#include <string>  
#include <stdio.h>
#include <iostream>

using namespace std;

typedef BOOL(__stdcall * pfnGetSystemTimes)(LPFILETIME lpIdleTime,
	LPFILETIME lpKernelTime, LPFILETIME lpUserTime);
typedef BOOL(WINAPI *P_GDFSE)(LPCTSTR, PULARGE_INTEGER,
	PULARGE_INTEGER, PULARGE_INTEGER);

static pfnGetSystemTimes s_pfnGetSystemTimes = NULL;

static HMODULE s_hKernel = NULL;

class ASSCheckHardware
{
public:
	ASSCheckHardware();
	~ASSCheckHardware();
	long CheckMemoryCurrentlyAvailable();
	int CpuUsage(void);
	void GetSystemTimesAddress();
	string SysInfoCpu();
	string SysInfoDisk();

private:
	Format* format = new Format();
	string description;
};

#endif
