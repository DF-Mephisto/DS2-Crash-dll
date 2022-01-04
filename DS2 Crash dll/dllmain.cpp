// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "dinput8.h"

HMODULE hInstance;

void Init()
{
	// Load the original dinput8.dll from the system directory
	char DInputDllName[MAX_PATH];
	GetSystemDirectoryA(DInputDllName, MAX_PATH);
	strcat_s(DInputDllName, "\\dinput8.dll");
	DInput8DLL = LoadLibraryA(DInputDllName);
	if (DInput8DLL > (HMODULE)31)
	{
		OriginalFunction = (DirectInput8Create_t)GetProcAddress(DInput8DLL, "DirectInput8Create");
	}
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		hInstance = hModule;

		Init();
		SysHook = SetWindowsHookEx(WH_GETMESSAGE, keyDownHook, hInstance, GetCurrentThreadId());

		par.enabled = false;
		CreateThread(NULL, 0, CrashProc, &par, 0, NULL);

		break;
	}
    case DLL_THREAD_ATTACH:
	{
		
		break;
	}
    case DLL_THREAD_DETACH:
	{
		
		break;
	}
    case DLL_PROCESS_DETACH:
	{
		UnhookWindowsHookEx(SysHook);
		break;
	}
    }
    return TRUE;
}

