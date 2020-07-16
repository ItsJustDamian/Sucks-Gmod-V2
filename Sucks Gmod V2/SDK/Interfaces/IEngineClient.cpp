#include "IEngineClient.h"

VMatrix IEngineClient::GetViewMatrix()
{
	typedef const VMatrix&(__thiscall * fn)(void*);
	return CallVFunc<fn>(this, 36)(this);
}

int IEngineClient::GetMaxClients()
{
	typedef int(__thiscall * fn)(void*);
	return CallVFunc<fn>(this, 21)(this);
}

void IEngineClient::GetScreenSize(int & width, int & height)
{
	typedef void(__thiscall * fn)(void*, int&, int&);
	CallVFunc<fn>(this, 5)(this, width, height);
}

int IEngineClient::GetLocalPlayer()
{
	typedef int(__thiscall * fn)(void*);
	return CallVFunc<fn>(this, 12)(this);
}

bool IEngineClient::GetPlayerInfo(int id, playerInfo* plrinfo)
{
	typedef bool(__thiscall * fn)(void*, int, void*);
	return CallVFunc<fn>(this, 8)(this, id, plrinfo);
}
