#include <iostream>
#include <stdio.h>
#include <ctime>
#include <cstdint>
#include <cstdlib>
#include "CellularAutomata\CellularAutomata.h"
#include "CellularAutomata\CAtest.h"
// 100 000 = ~50 sec
//  95 000 = ~40 sec
//  90 000 = ~18 sec
// const int size = 40;

int main()
{
	
	//std::srand((unsigned int)time_t(NULL));
	//for (int x = 0; x < 10; x++)
	//	for (int y = 0; y < 10; y++)
	//		std::cout << (std::rand() % 100 < 40 ? '#' : '.');
	bool run = true;
	CATest::GetInstance().Init(20, 20, 4, 3, 2, 50, 25);
	while (run)
	{
		int x = 0;
		CATest::GetInstance().EmptyCave();
		CATest::GetInstance().RandomizeCave();
		CATest::GetInstance().PrintCave();
		std::cin >> x;
		if (x == 1) run = false;
	}
	//CellularAutomata::GetInstance().Init(5, 5, 50, 50, 45);

	//std::srand((unsigned int)time(NULL));
	//std::clock_t begin = clock();
	//__int8** test;	// __int8 är chars! :(
	//// Allocated memory
	//test = new __int8*[size];
	//for (int i = 0; i < size; i++) {
	//	test[i] = new __int8[size];
	//	//std::cout << i << ", ";
	//}
	//std::clock_t end = clock();

	//for (int i = 0; i < size; i++)
	//{
	//	for (int j = 0; j < size; j++)
	//		test[i][j] = std::rand() % 3;
	//}

	//double elapsedSecs = double(end - begin) / CLOCKS_PER_SEC;
	//std::cout << "Elapsed seconds since launch: " << elapsedSecs << "\n";
	//for (int i = 0; i < size; i++)
	//{
	//	for (int j = 0; j < size; j++)
	//		std::cout << test[i][j] << ",";
	//	//std::cout << "\n";
	//}
	//std::cout << "Elapsed seconds since launch: " << elapsedSecs << "\n";
	//std::cin.get();
}

//// Exempelkod för beräkning av CPU usage.
//// CpuUsage.cpp : Defines the entry point for the console application.
////
//
//#include <Windows.h>
//#include <iostream>
//#include <iomanip>
//
//using namespace std;
//
//ULONGLONG subtractTime(const FILETIME &a, const FILETIME &b)
//{
//	LARGE_INTEGER la, lb;
//	la.LowPart = a.dwLowDateTime;
//	la.HighPart = a.dwHighDateTime;
//	lb.LowPart = b.dwLowDateTime;
//	lb.HighPart = b.dwHighDateTime;
//
//	return la.QuadPart - lb.QuadPart;
//}
//
//float getUsage(FILETIME *prevSysKernel, FILETIME *prevSysUser,
//	FILETIME *prevProcKernel, FILETIME *prevProcUser,
//	bool firstRun = false)
//{
//	FILETIME sysIdle, sysKernel, sysUser;
//	FILETIME procCreation, procExit, procKernel, procUser;
//
//	if (!GetSystemTimes(&sysIdle, &sysKernel, &sysUser) ||
//		!GetProcessTimes(GetCurrentProcess(), &procCreation, &procExit, &procKernel, &procUser))
//	{
//		// can't get time info so return
//		return -1.;
//	}
//
//	// check for first call
//	if (firstRun)
//	{
//		// save time info before return
//		prevSysKernel->dwLowDateTime = sysKernel.dwLowDateTime;
//		prevSysKernel->dwHighDateTime = sysKernel.dwHighDateTime;
//
//		prevSysUser->dwLowDateTime = sysUser.dwLowDateTime;
//		prevSysUser->dwHighDateTime = sysUser.dwHighDateTime;
//
//		prevProcKernel->dwLowDateTime = procKernel.dwLowDateTime;
//		prevProcKernel->dwHighDateTime = procKernel.dwHighDateTime;
//
//		prevProcUser->dwLowDateTime = procUser.dwLowDateTime;
//		prevProcUser->dwHighDateTime = procUser.dwHighDateTime;
//
//		return -1.0;
//	}
//
//	ULONGLONG sysKernelDiff = subtractTime(sysKernel, *prevSysKernel);
//	ULONGLONG sysUserDiff = subtractTime(sysUser, *prevSysUser);
//
//	ULONGLONG procKernelDiff = subtractTime(procKernel, *prevProcKernel);
//	ULONGLONG procUserDiff = subtractTime(procUser, *prevProcUser);
//
//	ULONGLONG sysTotal = sysKernelDiff + sysUserDiff;
//	ULONGLONG procTotal = procKernelDiff + procUserDiff;
//
//	return (float)((100.0 * procTotal) / sysTotal);
//}
//
//int main()
//{
//	FILETIME prevSysKernel, prevSysUser;
//	FILETIME prevProcKernel, prevProcUser;
//	float usage = 0.0;
//	float min = 0.0f, max = 0.0f, temp = 0.0f;
//
//	// first call
//	usage = getUsage(&prevSysKernel, &prevSysUser, &prevProcKernel, &prevProcUser, true);
//
//	// do something to use some cpu
//	for (int i = 1; i<1000000; i++)
//	{
//		srand(i);
//		int r = rand();
//		usage = getUsage(&prevSysKernel, &prevSysUser, &prevProcKernel, &prevProcUser);
//		cout << "CPU% = " << setiosflags(ios::fixed) << setprecision(2) << usage << "\n";
//		temp = usage;
//		std::cout << "sizeOf() = " << sizeof(int)*temp << "\n";
// 		if (temp > max) max = temp;
//		else if (temp < min) min = temp;
//	}
//	std::cout << "min = " << min << "\n";
//	std::cout << "max = " << max << "\n";
//	//wait 1 second
//	Sleep(1000);
//
//	// the actual cpu usage
//	usage = getUsage(&prevSysKernel, &prevSysUser, &prevProcKernel, &prevProcUser);
//	cout << "CPU% = " << setiosflags(ios::fixed) << setprecision(2) << usage;
//
//
//	return 0;
//}
