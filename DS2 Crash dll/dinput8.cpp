// DS2 Crash dll.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "dinput8.h"

DirectInput8Create_t OriginalFunction = nullptr;
HMODULE DInput8DLL = nullptr;
HHOOK SysHook;
PARAMS par;

DINPUT8_API HRESULT DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, LPUNKNOWN punkOuter)
{
	if (OriginalFunction)
	{
		return OriginalFunction(hinst, dwVersion, riidltf, ppvOut, punkOuter);
	}
	return S_FALSE;
}

LRESULT CALLBACK keyDownHook(int code, WPARAM wParam, LPARAM lParam)
{
	if (code == HC_ACTION && 
		((MSG*)lParam)->message == WM_KEYDOWN &&  
		FindWindow(NULL, L"DARK SOULS II") == ((MSG*)lParam)->hwnd)
	{
		switch (((MSG*)lParam)->wParam)
		{
		case VK_F1:
			MessageBeep(0);
			if (!par.enabled)
				WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), L"Autocrash enabled\n", wcslen(L"Autocrash enabled\n"), 0, 0);
			par.enabled = true;
			break;

		case VK_F2:
			MessageBeep(0);
			if (par.enabled)
				WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), L"Autocrash disabled\n", wcslen(L"Autocrash disabled\n"), 0, 0);
			par.enabled = false;
			break;

		case VK_F3:
			MessageBeep(0);
			createConsole();
			break;

		case VK_F4:
			MessageBeep(0);
			FreeConsole();
			break;
		}
		//wstring str = to_wstring(enabled) + L" " + to_wstring(!enabled);
		//MessageBox(NULL, str.c_str(), L"Info", MB_OK);
		//MessageBox(NULL, L"Pressed", L"Info", MB_OK);
		//MessageBox(NULL, to_wstring(par.enabled).c_str(), L"Info", MB_OK);
	}

	return CallNextHookEx(SysHook, code, wParam, lParam);
}

DWORD WINAPI CrashProc(CONST LPVOID lpParam) {
	
	PPARAMS params = (PPARAMS)lpParam;

	bool newPlayer = true;
	int level = 0;

	while (true)
	{

		WORD host = readHostility();

		if (host == 4112 || host == 4113)
		{
			if (newPlayer)
			{
				level = readLevel();
				newPlayer = false;

				const wchar_t* name = nullptr;

				if (name = readName())
				{
					wchar_t buf[80];
					wcscpy_s(buf, 80, name);
					wcscat_s(buf, 80, L"\t");
					wcscat_s(buf, 80, to_wstring(level).c_str());
					wcscat_s(buf, 80, L"\n");

					HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
					WriteConsoleW(h, buf, wcslen(buf), 0, 0);
				}
			}

			//wstring str = to_wstring(params->enabled);
			//MessageBox(NULL, str.c_str(), L"Info", MB_OK);

			if (level > 155 && params->enabled)
				crashProc((UINT64)GetModuleHandle(L"DarkSoulsII.exe"));
		}
		else
		{
			newPlayer = true;
		}

		Sleep(1000);
	}

	return 0;
}

void createConsole()
{
	if (GetConsoleWindow())
		return;

	AllocConsole();
	
	HWND handle = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(handle, false);
	DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_GREEN);

	WriteConsoleW(h, L"Made by Mephisto\n", wcslen(L"Made by Mephisto\n"), 0, 0);
	WriteConsoleW(h, L"Controls:\n", wcslen(L"Controls:\n"), 0, 0);
	WriteConsoleW(h, L"F1 - Enable autocrash 155+ players on both arenas\n", wcslen(L"F1 - Enable autocrash 155+ players on both arenas\n"), 0, 0);
	WriteConsoleW(h, L"F2 - Disable autocrash\n", wcslen(L"F2 - Disable autocrash\n"), 0, 0);
	WriteConsoleW(h, L"F3 - Enable console\n", wcslen(L"F3 - Enable console\n"), 0, 0);
	WriteConsoleW(h, L"F4 - Disable console\n", wcslen(L"F4 - Disable console\n"), 0, 0);

	WriteConsoleW(h, L"\n***************\n\n", wcslen(L"\n***************\n\n"), 0, 0);

	WriteConsoleW(h, par.enabled ? L"Autocrash enabled\n" : L"Autocrash disabled\n", 
		par.enabled ? wcslen(L"Autocrash enabled\n") : wcslen(L"Autocrash disabled\n"), 0, 0);
}