/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#pragma once
#include "ILuaInterface.h"
#include "../../MainHeader.h"
#include "../../Typedefs.h"

enum LuaInterfaceType : uchar
{
	LUAINTERFACE_CLIENT = 0,
	LUAINTERFACE_SERVER = 1,
	LUAINTERFACE_MENU = 2
};

class ILuaInterface;

class ILuaShared
{
public:
	virtual void			Destructor();
	virtual void			Init(void*, bool, void* *, void*);
	virtual void			Shutdown(void);
	virtual void			DumpStats(void);
	virtual ILuaInterface*	CreateLuaInterface(LuaInterfaceType type, bool);
	virtual int				CloseLuaInterface(ILuaInterface*);
	virtual ILuaInterface*	GetLuaInterface(LuaInterfaceType type);
	virtual void			LoadFile(void*, void*, bool, bool);
	virtual void			GetCache(void*);
	virtual void			MountLua(char  const*);
	virtual void			MountLuaAdd(char  const*, char  const*);
	virtual void			UnMountLua(char  const*);
	virtual void			SetFileContents(char  const*, char  const*);
	virtual void			SetLuaFindHook(void *);
	virtual void			FindScripts(void*, void*, void*);

	ILuaInterface*			CreateInterface(LuaInterfaceType state);
};

#define LUASHARED_INTERFACE_VERSION "LUASHARED003"