/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#include "GmodSDK.h"

void GmodSDK::init()
{
	luaSharedModule = GetModuleHandleA("lua_shared.dll");

	luaL_loadString = (_luaL_loadString)GetProcAddress(luaSharedModule, "luaL_loadstring");
	lua_pCall = (_lua_pCall)GetProcAddress(luaSharedModule, "lua_pcall");
	lua_remove = (_lua_remove)GetProcAddress(luaSharedModule, "lua_remove");
	lua_tolstring = (_lua_tolstring)GetProcAddress(luaSharedModule, "lua_tolstring");
	luaL_loadfile = (_luaL_loadfile)GetProcAddress(luaSharedModule, "luaL_loadfile");

	UpdateScreenInfo();
}

void GmodSDK::RunString(const char * lua)
{
	if ((DWORD)Interfaces->LuaShared->GetLuaInterface(LUAINTERFACE_CLIENT) == NULL)
		Logger->ErrorMsg("LuaInterface is not responsive, are you ingame?");
	else
	{
		if (Interfaces->LuaShared->GetLuaInterface(LUAINTERFACE_CLIENT) != G::LuaInterface)
			G::LuaInterface = Interfaces->LuaShared->CreateInterface(LUAINTERFACE_CLIENT);

		G::LuaInterface->runstring("Lua Executor ", "", lua, true, true);
	}
}

void GmodSDK::RunString_Naked(const char * lua)
{
	if ((DWORD)Interfaces->LuaShared->GetLuaInterface(LUAINTERFACE_CLIENT) == NULL)
		Logger->ErrorMsg("LuaInterface is not responsive, are you ingame?");
	else
	{
		if (Interfaces->LuaShared->GetLuaInterface(LUAINTERFACE_CLIENT) != G::LuaInterface)
			G::LuaInterface = Interfaces->LuaShared->CreateInterface(LUAINTERFACE_CLIENT);

		G::LuaInterface->runstring_naked("Lua Executor ", "", lua, true, true);
	}
}

void GmodSDK::RunLua(const char * lua)
{
	if (luaL_loadString || lua_pCall)
	{
		DWORD LuaIFace = (DWORD)Interfaces->LuaShared->GetLuaInterface(LUAINTERFACE_CLIENT);

		if (LuaIFace != NULL)
		{
			DWORD pGLuaState = *(DWORD*)(LuaIFace + 0x4);

			if (pGLuaState != NULL)
			{
				if (luaL_loadString((void*)pGLuaState, (char*)lua))
				{
					if (fn_WarnMsg == NULL)
						fn_WarnMsg = (fnMsg)GetProcAddress(GetModuleHandleA("tier0.dll"), "Warning");

					Logger->ForceColor(4);
					printf("[In-Game]: Error: %s\n", lua_tolstring((void*)pGLuaState, -1, NULL));
					fn_WarnMsg("[Error][Sucks Gmod - Lua Executor]: %s\n", lua_tolstring((void*)pGLuaState, -1, NULL));
					Logger->ForceResetColor();
					lua_remove((void*)pGLuaState, -1);
				}
				else lua_pCall((void*)pGLuaState, 0, -1, 0);
			}
			else Logger->ErrorMsg("Failed to get GLuaState");
		}
		else Logger->ErrorMsg("Failed to get LUAINTERFACE_CLIENT, make sure you are In-Game!");
	}
	else Logger->ErrorMsg("Failed to hook luaL_loadString or lua_pCall");
}

void GmodSDK::RunLuaFile(char * file)
{
}

void GmodSDK::UpdateScreenInfo()
{
	const char * windowName = "Garry's Mod";
		
	info.window = FindWindowA(NULL, windowName);

	if (!info.window)
	{
		Logger->ErrorMsg("Failed to get window HWND!");
		return;
	}

	info.windowName = windowName;

	RECT GameRect;
	if (!GetWindowRect(info.window, &GameRect))
	{
		Logger->ErrorMsg("Failed to get window RECT!");
		return;
	}

	info.x = GameRect.left;
	info.y = GameRect.top;
	info.w = GameRect.right - GameRect.left;
	info.h = GameRect.bottom - GameRect.top;

	Logger->Log("Screen info updated!");
}
