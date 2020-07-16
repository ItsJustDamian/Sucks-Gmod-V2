/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#pragma once
#include "MainHeader.h"
#include "SDK/Classes/CUserCmd.h"

class CUserCmd;

#ifndef typedefs
#define typedefs
	typedef unsigned char uchar;

	typedef void * (__cdecl * tCreateInterface)(const char * name, int * returnCode);
	typedef HRESULT(__stdcall * EndSceneFn)(IDirect3DDevice9 * pDevice);
	typedef long(__stdcall* resetFn)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
	typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

	//typedef bool(__stdcall * CreateMoveFn)(float flInputSampleTime, CUserCmd *cmd);
	typedef int(__stdcall * CreateMoveFn)(float, CUserCmd*);

	typedef HCURSOR(__cdecl* lock)();
	typedef HCURSOR(__cdecl* unlock)();

	typedef int(__cdecl* _luaL_loadString)(void* LState, char* LLuaCode);
	typedef int(__cdecl* _lua_pCall)(void* LState, int nargs, int nresults, int errfunc);
	typedef int(__cdecl* _lua_remove)(void* LState, int t);
	typedef int(__cdecl* _lua_tolstring)(void* LState, int a2, size_t *a3);
	typedef int(__cdecl* _luaL_loadfile)(void* LState, char* file);

	typedef void(__cdecl* fnMsg)(char const* pMsg, ...);
#endif