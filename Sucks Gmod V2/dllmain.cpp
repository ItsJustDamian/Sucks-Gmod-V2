#include "MainHeader.h"

DWORD WINAPI MainThread(LPVOID lpParam)
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);

	Logger->Log("Loading Sucks Gmod...");

	G::init();
	
	Interfaces = new CInterfaces();
	Hooks = new CHooks();
	gmodSDK = new GmodSDK();
	DrawLib = new CDrawLib();
	
	gmodSDK->init();
	Interfaces->init();
	Hooks->init();

	G::LuaInterface = Interfaces->LuaShared->CreateInterface(LUAINTERFACE_CLIENT); // Create our own lua interface :)

	int width, height;
	Interfaces->EngineClient->GetScreenSize(width, height);
	printf("Size: %ix%i\n", width, height);

	while (!GetAsyncKeyState(VK_END))
	{
		Sleep(100);
	}

	Hooks->shutdown();
	G::shutdown();

	delete DrawLib;
	delete gmodSDK;
	delete Hooks;
	delete Interfaces;

	FreeLibraryAndExitThread((HMODULE)lpParam, 0);
	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		HANDLE handle = CreateThread(0, 0, MainThread, hModule, 0, 0);

		if (!handle)
			return FALSE;

		CloseHandle(handle);
		return TRUE;
	}

	return FALSE;
}