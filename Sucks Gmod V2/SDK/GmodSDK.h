/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#pragma once
#include "../MainHeader.h"

struct ScreenInfo { HWND window; const char* windowName; int x, y, w, h; };

class GmodSDK
{
private:
	HMODULE luaSharedModule;
	_luaL_loadString luaL_loadString;
	_lua_pCall lua_pCall;
	_lua_remove lua_remove;
	_lua_tolstring lua_tolstring;
	_luaL_loadfile luaL_loadfile;
	fnMsg fn_Msg;
	fnMsg fn_WarnMsg;

public:
	ScreenInfo info = { 0, 0, 0, 0 };

	void init();
	void RunString(const char * lua = "print('hello world')");
	void RunString_Naked(const char * lua = "print('hello world')");
	void RunLua(const char * lua = "print('hello world')");
	void RunLuaFile(char * file);

	void UpdateScreenInfo();
};

inline GmodSDK * gmodSDK;