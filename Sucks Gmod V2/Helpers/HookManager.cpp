#include "HookManager.h"

void CHookManager::setup(const char * szModule, const char * szPattern, int offset)
{
	VMThook = new CVMTHookManager(**(DWORD64****)(PointerManager->FindPattern(szModule, szPattern) + offset));
}

void CHookManager::hook(void * func, int vIndex)
{
	if (originalFuncArr[vIndex] != nullptr)
	{
		Logger->ErrorMsg("Failed to hook, already hooked this vFunc!");
		return;
	}

	originalFuncArr[vIndex] = VMThook->HookFunction(vIndex, func);
	VMThook->HookTable(true);
}

void CHookManager::close()
{
	for (int i = 0; i <= 512; i++)
	{
		if (get_original(i) != nullptr)
			VMThook->HookFunction(i, get_original(i));
	}

	VMThook->HookTable(false);
	delete VMThook;
}

void * CHookManager::get_original(int vIndex)
{
	if (originalFuncArr[vIndex] == nullptr)
		return nullptr;
	else
		return originalFuncArr[vIndex];
}