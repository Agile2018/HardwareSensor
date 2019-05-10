#include "ASSCheckHardware.h"

ASSCheckHardware::ASSCheckHardware()
{
}

ASSCheckHardware::~ASSCheckHardware()
{
}

void ASSCheckHardware::GetSystemTimesAddress() {
	if (s_hKernel == NULL)
	{
		s_hKernel = LoadLibrary(L"Kernel32.dll");
		if (s_hKernel != NULL)
		{
			s_pfnGetSystemTimes = (pfnGetSystemTimes)GetProcAddress(s_hKernel,
				"GetSystemTimes");
			if (s_pfnGetSystemTimes == NULL)
			{
				FreeLibrary(s_hKernel); s_hKernel = NULL;
			}
		}
	}
}

int ASSCheckHardware::CpuUsage() {
	FILETIME               ft_sys_idle;
	FILETIME               ft_sys_kernel;
	FILETIME               ft_sys_user;

	ULARGE_INTEGER         ul_sys_idle;
	ULARGE_INTEGER         ul_sys_kernel;
	ULARGE_INTEGER         ul_sys_user;

	static ULARGE_INTEGER    ul_sys_idle_old;
	static ULARGE_INTEGER  ul_sys_kernel_old;
	static ULARGE_INTEGER  ul_sys_user_old;

	CHAR  usage = 0;

	s_pfnGetSystemTimes(&ft_sys_idle,    /* System idle time */
		&ft_sys_kernel,  /* system kernel time */
		&ft_sys_user);   /* System user time */

	CopyMemory(&ul_sys_idle, &ft_sys_idle, sizeof(FILETIME));
	CopyMemory(&ul_sys_kernel, &ft_sys_kernel, sizeof(FILETIME));
	CopyMemory(&ul_sys_user, &ft_sys_user, sizeof(FILETIME));

	usage =
		(
		(
			(
			(
				(ul_sys_kernel.QuadPart - ul_sys_kernel_old.QuadPart) +
				(ul_sys_user.QuadPart - ul_sys_user_old.QuadPart)
				)
				-
				(ul_sys_idle.QuadPart - ul_sys_idle_old.QuadPart)
				)
			*
			(100)
			)
			/
			(
			(ul_sys_kernel.QuadPart - ul_sys_kernel_old.QuadPart) +
				(ul_sys_user.QuadPart - ul_sys_user_old.QuadPart)
				)
			);

	ul_sys_idle_old.QuadPart = ul_sys_idle.QuadPart;
	ul_sys_user_old.QuadPart = ul_sys_user.QuadPart;
	ul_sys_kernel_old.QuadPart = ul_sys_kernel.QuadPart;

	return (int)usage;
}

long ASSCheckHardware::CheckMemoryCurrentlyAvailable() {

	MEMORYSTATUS MemoryStatus;
	ZeroMemory(&MemoryStatus, sizeof(MEMORYSTATUS));
	MemoryStatus.dwLength = sizeof(MEMORYSTATUS);

	GlobalMemoryStatus(&MemoryStatus);
	if (MemoryStatus.dwTotalPhys == -1)
	{
		MEMORYSTATUSEX MemoryStatusEx;
		GlobalMemoryStatusEx(&MemoryStatusEx);
		return (long)(MemoryStatusEx.ullTotalPhys / (1024 * 1024));
	}
	return (long)((MemoryStatus.dwTotalPhys - MemoryStatus.dwAvailPhys) / MEGABYTE);
}

string ASSCheckHardware::SysInfoCpu() {
	SYSTEM_INFO siSysInfo;

	// Copy the hardware information to the SYSTEM_INFO structure. 

	GetSystemInfo(&siSysInfo);

	// Display the contents of the SYSTEM_INFO structure. 
	description += format->FormatString("CPU HARDWARE REPORT: \n");
	description += format->FormatString("OEM ID : %u\n", siSysInfo.dwOemId);
	description += format->FormatString("Processor Architecture : %u\n", siSysInfo.wProcessorArchitecture);
	description += format->FormatString("Number of processors: %u\n",
		siSysInfo.dwNumberOfProcessors);
	description += format->FormatString("Page size: %u\n", siSysInfo.dwPageSize);
	description += format->FormatString("Processor type: %u\n", siSysInfo.dwProcessorType);
	description += format->FormatString("Minimum application address: %lx\n",
		siSysInfo.lpMinimumApplicationAddress);
	description += format->FormatString("Maximum application address: %lx\n",
		siSysInfo.lpMaximumApplicationAddress);
	description += format->FormatString("Active processor mask: %u\n",
		siSysInfo.dwActiveProcessorMask);
	
	//cout << "CPU: " << description << endl;
	return description;
}

string ASSCheckHardware::SysInfoDisk() {
	string detailDisk;

	BOOL  fResult;

	char  *pszDrive = NULL,
		szDrive[4];

	DWORD dwSectPerClust,
		dwBytesPerSect,
		dwFreeClusters,
		dwTotalClusters;

	P_GDFSE pGetDiskFreeSpaceEx = NULL;

	unsigned __int64 i64FreeBytesToCaller,
		i64TotalBytes,
		i64FreeBytes;

	/*
	   Command line parsing.

	   If the drive is a drive letter and not a UNC path, append a
	   trailing backslash to the drive letter and colon.  This is
	   required on Windows 95 and 98.
	*/
	/*if (argc != 2)
	{
		printf("usage:  %s <drive|UNC path>\n", argv[0]);
		printf("\texample:  %s C:\\\n", argv[0]);
		return;
	}*/
	char argv[] = { 'C', ':' };

	pszDrive = argv;

	if (pszDrive[1] == ':')
	{
		szDrive[0] = pszDrive[0];
		szDrive[1] = ':';
		szDrive[2] = '\\';
		szDrive[3] = '\0';

		pszDrive = szDrive;
	}

	/*
	   Use GetDiskFreeSpaceEx if available; otherwise, use
	   GetDiskFreeSpace.

	   Note: Since GetDiskFreeSpaceEx is not in Windows 95 Retail, we
	   dynamically link to it and only call it if it is present.  We
	   don't need to call LoadLibrary on KERNEL32.DLL because it is
	   already loaded into every Win32 process's address space.
	*/
	pGetDiskFreeSpaceEx = (P_GDFSE)GetProcAddress(
		GetModuleHandleW(L"kernel32.dll"),
		"GetDiskFreeSpaceExA");
	if (pGetDiskFreeSpaceEx)
	{
		fResult = pGetDiskFreeSpaceEx((LPCWSTR)pszDrive,
			(PULARGE_INTEGER)&i64FreeBytesToCaller,
			(PULARGE_INTEGER)&i64TotalBytes,
			(PULARGE_INTEGER)&i64FreeBytes);
		if (fResult)
		{
			detailDisk = format->FormatString("-----------------------------------------\n");
			detailDisk += format->FormatString("HARD DRIVE REPORT\n");
			//printf("\n\nGetDiskFreeSpaceEx reports\n\n");
			detailDisk += format->FormatString("Available space to caller = %I64u MB\n",
				i64FreeBytesToCaller / (1024 * 1024));

			//printf("Available space to caller = %I64u MB\n",
			//	i64FreeBytesToCaller / (1024 * 1024));
			detailDisk += format->FormatString("Total space = %I64u MB\n",
				i64TotalBytes / (1024 * 1024));

			//printf("Total space               = %I64u MB\n",
			//	i64TotalBytes / (1024 * 1024));
			detailDisk += format->FormatString("Free space on drive = %I64u MB\n",
				i64FreeBytes / (1024 * 1024));

			//printf("Free space on drive       = %I64u MB\n",
			//	i64FreeBytes / (1024 * 1024));
		}
	}
	else
	{
		fResult = GetDiskFreeSpace((LPCWSTR)pszDrive,
			&dwSectPerClust,
			&dwBytesPerSect,
			&dwFreeClusters,
			&dwTotalClusters);
		if (fResult)
		{
			/* force 64-bit math */
			i64TotalBytes = (__int64)dwTotalClusters * dwSectPerClust *
				dwBytesPerSect;
			i64FreeBytes = (__int64)dwFreeClusters * dwSectPerClust *
				dwBytesPerSect;

			//printf("GetDiskFreeSpace reports\n\n");
			detailDisk += format->FormatString("Free space  = %I64u MB\n",
				i64FreeBytes / (1024 * 1024));

			//printf("Free space  = %I64u MB\n",
			//	i64FreeBytes / (1024 * 1024));
			detailDisk += format->FormatString("Total space = %I64u MB\n",
				i64TotalBytes / (1024 * 1024));

			//printf("Total space = %I64u MB\n",
			//	i64TotalBytes / (1024 * 1024));
		}
	}

	//if (!fResult)
	//	printf("error: %lu:  could not get free space for \"%s\"\n",
	//		GetLastError(), argv[1]);
	//cout << "DISK: " << detailDisk << endl;
	return detailDisk;
}
