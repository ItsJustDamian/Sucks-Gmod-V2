#pragma once
#include "../MainHeader.h"

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

class CPointerManager
{
public:
	DWORD64 GetModuleBase(const char* szModule);
	DWORD64 GetModuleSize(const char* szModule);
	DWORD64 FindPattern(const char* szModule, const char* szPattern);
	DWORD64 GetPointer(const char* szModule, const char* szPattern, int offset = 0, bool removeBase = false, int extra = 0);
};

inline CPointerManager * PointerManager;