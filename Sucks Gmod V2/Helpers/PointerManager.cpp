#include "PointerManager.h"

DWORD64 CPointerManager::GetModuleBase(const char * szModule)
{
	return (DWORD64)GetModuleHandleA(szModule);
}

DWORD64 CPointerManager::GetModuleSize(const char * szModule)
{
	DWORD64 dwModuleBase = GetModuleBase(szModule);
	if (dwModuleBase == NULL)
		return NULL;

	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)dwModuleBase;
	PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)(dwModuleBase + pDosHeader->e_lfanew);

	return pNtHeaders->OptionalHeader.SizeOfImage;
}

DWORD64 CPointerManager::FindPattern(const char * szModule, const char * szPattern)
{
	DWORD64 dwModuleBase = GetModuleBase(szModule);
	if (dwModuleBase == NULL) {
		Logger->ErrorMsg("CMemory::CPattern::Find couldn't find module.");
		return NULL;
	}

	DWORD64 dwModuleSize = GetModuleSize(szModule);
	if (dwModuleSize == NULL) {
		Logger->ErrorMsg("CMemory::CPattern::Find couldn't find module size.");
		return NULL;
	}

	DWORD64 dwModuleStart = dwModuleBase;
	DWORD64 dwModuleEnd = dwModuleBase + dwModuleSize;

	const char* szPatternCurrent = szPattern;
	DWORD64 dwFirstMatch = NULL;

	for (PBYTE pAddress = (PBYTE)dwModuleStart; pAddress < (PBYTE)dwModuleEnd; pAddress++)
	{
		if (*pAddress != getByte(szPatternCurrent) && *szPatternCurrent != '\?') {
			dwFirstMatch = NULL;
			szPatternCurrent = szPattern;
			continue;
		}

		if (!dwFirstMatch)
			dwFirstMatch = (DWORD64)pAddress;

		szPatternCurrent += 3;
		if (szPatternCurrent[-1] == NULL)
			return dwFirstMatch;
	}
	return NULL;
}

DWORD64 CPointerManager::GetPointer(const char * szModule, const char * szPattern, int offset, bool removeBase, int extra)
{
	DWORD64 SigScanResult = FindPattern(szModule, szPattern) + offset;
	DWORD64 tmpStorage = *(DWORD64*)(SigScanResult);

	if (extra > 0)
		tmpStorage += extra;

	if (removeBase)
		tmpStorage -= (DWORD64)GetModuleHandleA(szModule);

	return tmpStorage;
}