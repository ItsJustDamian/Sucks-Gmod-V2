/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#include "Interfaces.h"

template<typename C>
inline C CInterfaces::GetInterface(const char * moduleName, const char * interfaceName)
{
	tCreateInterface CreateInterface = (tCreateInterface)GetProcAddress(GetModuleHandleA(moduleName), "CreateInterface");

	if (!CreateInterface)
	{
		Logger->ErrorMsg("Failed to get CreateInterface Export!");
		return nullptr;
	}

	int returnCode = 0;
	void* iface = CreateInterface(interfaceName, &returnCode);

	return (C)iface;
}

void CInterfaces::init()
{
	this->ClientEntityList = GetInterface<IClientEntityList*>("client.dll", VCLIENTENTITYLIST_INTERFACE_VERSION);
	this->LuaShared = GetInterface<ILuaShared*>("lua_shared.dll", LUASHARED_INTERFACE_VERSION);
	this->Surface = GetInterface<ISurface*>("vguimatsurface.dll", VGUI_SURFACE_INTERFACE_VERSION);
	this->EngineClient = GetInterface<IEngineClient*>("engine.dll", "VEngineClient015");

	if (!this->ClientEntityList)
		Logger->ErrorMsg("ClientEntityList gave nullptr as interface!");

	if (!this->LuaShared)
		Logger->ErrorMsg("LuaShared gave nullptr as interface!");

	if (!this->Surface)
		Logger->ErrorMsg("Surface gave nullptr as interface!");

	if (!this->EngineClient)
		Logger->ErrorMsg("EngineClient gave nullptr as interface!");

	//this->ClientMode = GetInterface<IClientMode*>("client.dll", "VClient017");
}