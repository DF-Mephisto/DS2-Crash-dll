#pragma once

#include <unknwn.h>
#include "MemReader.h"

typedef struct
{
	bool enabled;
} PARAMS, *PPARAMS;

extern "C"
{
	int crashProc(DWORD64 baseAddr);
}

using DirectInput8Create_t = HRESULT(*)(
	HINSTANCE hinst,
	DWORD dwVersion,
	REFIID riidltf,
	LPVOID * ppvOut,
	LPUNKNOWN punkOuter
	);

extern DirectInput8Create_t OriginalFunction;
extern HMODULE DInput8DLL;
extern HHOOK SysHook;
extern PARAMS par;

DWORD WINAPI CrashProc(CONST LPVOID lpParam);
LRESULT CALLBACK keyDownHook(int code, WPARAM wParam, LPARAM lParam);
void createConsole();

extern "C"
{
	DINPUT8_API HRESULT DirectInput8Create(
		HINSTANCE hinst,
		DWORD dwVersion,
		REFIID riidltf,
		LPVOID * ppvOut,
		LPUNKNOWN punkOuter
	);
}