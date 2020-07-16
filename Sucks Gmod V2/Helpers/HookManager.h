#pragma once
#include "../MainHeader.h"
class CHookManager
{
private:
	CVMTHookManager * VMThook;
	void * originalFuncArr[512];

public:
	void setup(const char * szModule, const char * szPattern, int offset = 0);
	void hook(void * func, int vIndex);
	void close();
	void* get_original(int vIndex);
};