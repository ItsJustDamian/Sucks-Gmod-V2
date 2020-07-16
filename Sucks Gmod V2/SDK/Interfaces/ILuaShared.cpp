#include "ILuaShared.h"

ILuaInterface * ILuaShared::CreateInterface(LuaInterfaceType state)
{
	using fn = ILuaInterface * (__thiscall*)(void*, LuaInterfaceType);
	return CallVFunc<fn>(this, 6)(this, state);
}
