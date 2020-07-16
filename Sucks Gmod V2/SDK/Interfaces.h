/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#pragma once
#include "../MainHeader.h"

#include "Interfaces/IClientEntityList.h"
#include "Interfaces/ILuaInterface.h"
#include "Interfaces/ILuaShared.h"
#include "Interfaces/ISurface.h"
#include "Interfaces/IEngineClient.h"

class ILuaShared;
class IEngineClient;

class CInterfaces
{
public:
	template<typename C>
	C GetInterface(const char * moduleName, const char * interfaceName);
	void init();

	IClientEntityList * ClientEntityList = nullptr;
	ILuaShared * LuaShared = nullptr;
	ISurface * Surface = nullptr;
	IEngineClient * EngineClient = nullptr;
	//IClientMode * ClientMode = nullptr;
};

inline CInterfaces * Interfaces;