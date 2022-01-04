// DS2 Crash dll.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "MemReader.h"

using namespace std;

WORD readHostility()
{
	BYTE* module = (BYTE*)GetModuleHandle(L"DarkSoulsII.exe");
	module = module + 0x160DCD8;

	if (IsBadReadPtr(module, 8))
		return -1;

	module = ((BYTE*)*((DWORD64*)module)) + 0x20;

	if (IsBadReadPtr(module, 8))
		return -1;

	module = ((BYTE*)*((DWORD64*)module)) + 0x1E8;

	if (IsBadReadPtr(module, 8))
		return -1;

	module = ((BYTE*)*((DWORD64*)module)) + 0xB0;

	if (IsBadReadPtr(module, 8))
		return -1;

	module = ((BYTE*)*((DWORD64*)module)) + 0x3C;

	WORD* hostility = (WORD*)module;

	if (!IsBadWritePtr(hostility, 2))
		return *hostility;
}

DWORD readLevel()
{
	BYTE* module = (BYTE*)GetModuleHandle(L"DarkSoulsII.exe");
	module = module + 0x160DCD8;

	if (IsBadReadPtr(module, 8))
		return -1;

	module = ((BYTE*)*((DWORD64*)module)) + 0x20;

	if (IsBadReadPtr(module, 8))
		return -1;

	module = ((BYTE*)*((DWORD64*)module)) + 0x1E8;

	if (IsBadReadPtr(module, 8))
		return -1;

	module = ((BYTE*)*((DWORD64*)module)) + 0x390;

	if (IsBadReadPtr(module, 8))
		return -1;

	module = ((BYTE*)*((DWORD64*)module)) + 0x1C0;

	DWORD* level = (DWORD*)module;

	if (!IsBadWritePtr(level, 4))
		return *level;
}

const wchar_t* readName()
{
	BYTE* module = (BYTE*)GetModuleHandle(L"DarkSoulsII.exe");
	module = module + 0x160DCD8;

	if (IsBadReadPtr(module, 8))
		return nullptr;

	module = ((BYTE*)*((DWORD64*)module)) + 0x20;

	if (IsBadReadPtr(module, 8))
		return nullptr;

	module = ((BYTE*)*((DWORD64*)module)) + 0x234;

	wchar_t* name = (wchar_t*)module;

	if (!IsBadReadPtr(module, 64))
		return name;
}