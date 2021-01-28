//#pragma once
//
//#include <string>
//#include <iostream>
//#include <Windows.h>
//#include <Psapi.h>
//#include <TlHelp32.h>
//#include <io.h>
//
//using namespace std;
//
//namespace Injector
//{
//	extern bool Inject(string strProcessName, string strDLLPath);
//}
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <TlHelp32.h>

using namespace std;


DWORD procIdFromPN;

static DWORD GetThreadIDFromProcName(const char *ProcName)
{
	//create handle
	HANDLE thSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (thSnapShot == INVALID_HANDLE_VALUE)
	{
		printf("Error: failed create handle[INJECT]");
		return 0;
	}

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);

	//go through all the fucking processes and check for their names
	BOOL retval = Process32First(thSnapShot, &pe);
	while (retval)
	{

		if (!strcmp(pe.szExeFile, ProcName))
		{
			//stuff is correct, close the handle and return the ID
			CloseHandle(thSnapShot);
			return pe.th32ProcessID;
		}
		retval = Process32Next(thSnapShot, &pe);
	}
	printf("Error: game not found.\n");

	//close the handle
	CloseHandle(thSnapShot);

	return 0;
}

bool inject(const char *dllPath)
{
	procIdFromPN = GetThreadIDFromProcName("csgo.exe");

	if (procIdFromPN != 0)
	{
		HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procIdFromPN);
		if (processHandle == 0)
		{
			printf("inject failed: %d", GetLastError());
			return false;
		}

		char dll[MAX_PATH];

		GetFullPathNameA(dllPath, MAX_PATH, dll, NULL);



		//speaks for itself, retrieves loadlibrarya from the kernel
		LPVOID loadLibrary = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");

		LPVOID VirtualName = VirtualAllocEx(processHandle, NULL, strlen(dll), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

		//write path of our dll into the process so we can load it
		WriteProcessMemory(processHandle, VirtualName, dll, strlen(dll), NULL);

		//call thread to load our dll inside other process
		CreateRemoteThread(processHandle, NULL, NULL, (LPTHREAD_START_ROUTINE)loadLibrary, VirtualName, NULL, NULL);

		//close handle to process kek
		CloseHandle(processHandle);
		return true; //everything okido
	}
	else
		return false;
}


