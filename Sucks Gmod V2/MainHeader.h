#pragma once
#include <Windows.h>
#include <iostream>
#include <ctime>
#include <time.h>
#include <stdio.h>
#include <TlHelp32.h>
#include <string>
#include <sstream>
#include <d3d9.h>
#include <d3dx9.h>
#include <Psapi.h>
#include "detours.h"

#include "Typedefs.h"
#include "Globals.h"
#include "DrawLib.h"

#include "SDK/Utils.h"
#include "SDK/Interfaces.h"
#include "SDK/GmodSDK.h"
#include "SDK/Hooks.h"

#include "SDK/Classes/QAngle.h"
#include "SDK/Classes/Vector.h"
#include "SDK/Classes/C_BaseEntity.h"
#include "SDK/Classes/CUserCmd.h"
#include "SDK/Classes/GameEventListener.h"

#include "Helpers/VMTHook.h"
#include "Helpers/PointerManager.h"
#include "Helpers/HookManager.h"
#include "Helpers/Logger.h"

#include "SDK/Interfaces/IClientEntityList.h"
#include "SDK/Interfaces/ILuaInterface.h"
#include "SDK/Interfaces/ILuaShared.h"
#include "SDK/Interfaces/ISurface.h"
#include "SDK/Interfaces/IEngineClient.h"

#include "Features/Visuals.h"
#include "Features/Aimbot.h"
#include "Features/EntityInfo.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/TextEditor.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "psapi.lib")

template<typename FuncType>
inline FuncType CallVFunc(void * Class, int index)
{
	DWORD* table = *(DWORD**)Class;
	DWORD address = table[index];
	return (FuncType)address;
}

template <typename T>
inline T vFunc(void* pAddress, int iIndex)
{
	return (*reinterpret_cast<T**>(pAddress))[iIndex];
}

inline int RebaseAddy(int Offset, DWORD Base, const char* szModule)
{
	return ((Offset - Base) + (DWORD)GetModuleHandleA(szModule));
}