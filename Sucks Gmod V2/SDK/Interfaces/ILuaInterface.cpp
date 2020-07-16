#include "ILuaInterface.h"

DWORD64 ILuaInterface::GetState()
{
	return *(DWORD64*)((DWORD64)this + 0x4);
}

void ILuaInterface::runstring(const char * filename, const char * path, const char * stringToRun, bool run, bool showErrors)
{
	typedef void(__thiscall * fn)(void*, const char* filename, const char* path, const char* stringToRun, bool run, bool showErrors);
	CallVFunc<fn>(this, 92)(this, filename, path, stringToRun, run, showErrors);
}

void ILuaInterface::runstring_naked(const char * filename, const char * path, const char * stringToRun, bool run, bool showErrors)
{
	(*(int(_stdcall**)(const char* filename, const char* path, const char* stringToRun, bool run, bool showErrors, int idk, int idkagain))(this + 444))(
		filename,
		path,
		stringToRun,
		run,
		showErrors,
		1,
		1);
}
