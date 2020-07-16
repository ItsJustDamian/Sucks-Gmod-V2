#pragma once
#include "MainHeader.h"

#include "SDK/Interfaces.h"
#include "SDK/GmodSDK.h"
#include "SDK/Hooks.h"

class ILuaInterface;

namespace G
{
	inline DWORD64 ClientModule = 0;
	inline DWORD64 EngineModule = 0;
	inline ILuaInterface * LuaInterface;

	inline LPD3DXFONT EspTextFont[50];
	inline LPD3DXFONT DebugTextFont;

	namespace Variables
	{
		inline bool EspEnabled = false;
		inline bool EspSnaplinesEnabled = false;
		inline float boxColor[3] = {255, 0, 0};
		inline float textColor[3] = {255, 255, 255};

		inline bool SimpleCrosshair = false;
		inline bool FpsMeter = false;
		inline bool NearestEntInfo = false;

		inline bool AimbotEnabled = false;
		inline bool AimbotSmoothingEnabled = false;
		inline bool AimbotSilent = false;
		inline int AimbotSmoothing = 5;
		inline int AimbotFOV = 10;
	}

	inline void init()
	{
		G::ClientModule = (DWORD64)GetModuleHandleA("client.dll");
		G::EngineModule = (DWORD64)GetModuleHandleA("engine.dll");
	}

	inline void shutdown()
	{
		
	}
}