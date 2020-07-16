#pragma once
#pragma once
#include <Windows.h>
#ifdef _WIN64
#define _pdword		PDWORD64
#define _dword		DWORD64
#else
#define _pdword		PDWORD
#define _dword		DWORD
#endif
class CVMT
{
public:
	/*void* Hook(void* Instance, int Index, void* HookedFunc)
	{
	DWORD VirtualTable = *(DWORD*)Instance;
	DWORD VirtualFunction = VirtualTable + sizeof(DWORD) * Index;
	intptr_t OriginalFunction = *((DWORD*)VirtualFunction);
	DWORD OldProtect;
	VirtualProtect((LPVOID)VirtualFunction, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &OldProtect);
	*((DWORD*)VirtualFunction) = (DWORD)HookedFunc;
	VirtualProtect((LPVOID)VirtualFunction, sizeof(DWORD), OldProtect, &OldProtect);
	return (void*)OriginalFunction;
	}*/
	template< typename Function > Function getvfunc(PVOID Base, _dword Index)
	{

		_pdword* VTablePointer = (_pdword*)Base;
		_pdword VTableFunctionBase = *VTablePointer;
		_dword dwAddress = VTableFunctionBase[Index];
		return (Function)(dwAddress);
	}
	inline void* GetFunction(void* Instance, int Index)
	{
		_dword VirtualFunction = (*(_dword*)Instance) + sizeof(_dword) * Index;
		return (void*)*((_dword*)VirtualFunction);
	}

}; inline CVMT VMT;
#define k_page_writeable (PAGE_READWRITE | PAGE_EXECUTE_READWRITE)
#define k_page_readable (k_page_writeable|PAGE_READONLY|PAGE_WRITECOPY|PAGE_EXECUTE_READ|PAGE_EXECUTE_WRITECOPY)
#define k_page_offlimits (PAGE_GUARD|PAGE_NOACCESS)
/*Credits to null for helping me with this.*/
class CVMTHookManager
{
public:
	CVMTHookManager() {}
	/*Deconstructor*/
	~CVMTHookManager() {
		this->HookTable(false);
	}
	CVMTHookManager(void* Interface)
	{
		this->Init(Interface);
	}
	/*Inits the function*/
	bool Init(void* Interface)
	{
		pOrgTable = *(void**)Interface;
		this->count = this->GetCount();
		pCopyTable = malloc(sizeof(void*)* count);
		memcpy(pCopyTable, pOrgTable, sizeof(void*) * count);
		pObject = (_dword*)Interface;
		return true;
	}
	/*Hook/Unhook*/
	void HookTable(bool hooked)
	{
		if (hooked)
		{
			*pObject = (_dword)pCopyTable;
		}
		else
		{
			*pObject = (_dword)pOrgTable;
		}
	}
	/*Hooks function*/
	void* HookFunction(int Index, void* hkFunction)
	{
		if (Index < this->count && Index >= 0)
		{
			((_dword*)pCopyTable)[Index] = (_dword)hkFunction;
			return (void*)((_dword*)pOrgTable)[Index];
		}
		return NULL;
	}

private:
	/*Returns if you can read the pointer*/
	bool CanReadPointer(void* table)
	{
		MEMORY_BASIC_INFORMATION mbi;
		if (table == nullptr) return false;
		if (!VirtualQuery(table, &mbi, sizeof(mbi))) return false;
		if (mbi.Protect & k_page_offlimits) return false;
		return (bool)(mbi.Protect & k_page_readable);
	}
	/*Gets VMT count*/
	int GetCount()
	{
		int index = 0;
		void** table = ((void**)pOrgTable);
		for (void* fn; (fn = table[index]) != nullptr; index++)
		{
			if (!this->CanReadPointer(fn)) break;
		}
		return index;
	}
	int count;
	void* pCopyTable;
	_dword* pObject;
	void* pOrgTable;
};