/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#include "Hooks.h"

CHookManager * dxHookManager;
CHookManager * cmHookManager;
CVMTHookManager * cursorHook;

//Predefine Hooks
HRESULT __stdcall hkEndScene(IDirect3DDevice9 * pDevice);
long __stdcall hkReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters);
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool __stdcall hkCreateMove(float flInputSampleTime, CUserCmd *cmd);
HCURSOR hook();
//End

//Variables needed for hooks
WNDPROC oWndProc;
CreateMoveFn oCreateMove;
lock lockcursor = (lock)RebaseAddy(0x794F4E10, 0x794B0000, "vguimatsurface.dll"); //rebaseCursorPtr(0x794F4E10); //index 62
unlock unlockcursor = (unlock)RebaseAddy(0x794F7A30, 0x794B0000, "vguimatsurface.dll"); //rebaseCursorPtr(0x794F7A30); //index 61
bool menuOpen = false;
//End

void CHooks::init()
{
	dxHookManager = new CHookManager();
	//cmHookManager = new CHookManager();

	oWndProc = (WNDPROC)SetWindowLongPtr(gmodSDK->info.window, GWL_WNDPROC, (LONG_PTR)WndProc);
	dxHookManager->setup("shaderapidx9.dll", "A1 ?? ?? ?? ?? 50 8B 08 FF 51 0C", 0x1);
	dxHookManager->hook(hkEndScene, 42);
	dxHookManager->hook(hkReset, 16);

	/*cmHookManager->setup("client.dll", "55 8B EC E8 ? ? ? ? 8B C8 85 C9 75 06", 0x0);
	cmHookManager->hook(hkCreateMove, 24);*/

	oCreateMove = (CreateMoveFn)DetourFunction((PBYTE)RebaseAddy(0x10189280, 0x10000000, "client.dll"), (PBYTE)hkCreateMove);
	lockcursor = (HCURSOR(__cdecl*)())DetourFunction((PBYTE)RebaseAddy(0x794F4E10, 0x794B0000, "vguimatsurface.dll"), (PBYTE)hook);
}

void CHooks::shutdown()
{
	SetWindowLong(gmodSDK->info.window, GWL_WNDPROC, (LONG_PTR)oWndProc);

	dxHookManager->close();
	//cmHookManager->close();

	DetourFunction((PBYTE)RebaseAddy(0x794F4E10, 0x794B0000, "vguimatsurface.dll"), (PBYTE)lockcursor);

	delete dxHookManager;
	//delete cmHookManager;
}

// ACTUAL HOOKS DOWN HERE!!

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (menuOpen)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

int fps, cFps;
clock_t lastClock = 0;
std::stringstream ssText;
HRESULT __stdcall hkEndScene(IDirect3DDevice9 * pDevice)
{
	if (GetAsyncKeyState(VK_MULTIPLY) & 0x0001)
		menuOpen = !menuOpen;


	/*D3DRECT rect = {100, 100, 200, 200};
	pDevice->Clear(1, &rect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 255, 0, 0), 0, 0);*/

	static bool init = true;
	if (init)
	{
		init = false;

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		menu->StyleInit();

		ImGui_ImplWin32_Init(gmodSDK->info.window);
		ImGui_ImplDX9_Init(pDevice);

		DrawLib->SetD3DDevice(pDevice);

		

		for (int i = 1; i <= 50; i++)
		{
			G::EspTextFont[i] = DrawLib->CreateSurfaceFont(i, "Arial");
		}

		G::DebugTextFont = DrawLib->CreateSurfaceFont(28, "Impact");

		DrawLib->SetFont(G::EspTextFont[16]);
	}

	ImGui::GetIO().MouseDrawCursor = menuOpen;

	if (menuOpen)
	{
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		menu->RenderMenu();

		ImGui::EndFrame();
		ImGui::Render();

		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}

	if(G::Variables::EspEnabled)
		Visuals->DrawEsp();

	if (G::Variables::NearestEntInfo)
		EntityInfo->DrawInfo();

	if (G::Variables::SimpleCrosshair)
	{
		int s_Width, s_Height;
		Interfaces->EngineClient->GetScreenSize(s_Width, s_Height);

		DrawLib->SetDrawColor(255, 255, 255);
		DrawLib->DrawFilledRect((s_Width / 2) - 7.5, (s_Height / 2) - 1, 15, 2);
		DrawLib->DrawFilledRect((s_Width / 2) - 1, (s_Height / 2) - 7.5, 2, 15);
	}

	if (G::Variables::FpsMeter)
	{
		clock_t thisClock = clock();
		if ((((thisClock - lastClock) / (double)CLOCKS_PER_SEC)*1000.0) > 1000)
		{
			lastClock = thisClock;
			fps = cFps;
			cFps = 0;
		}
		else
			cFps++;


		ssText.str("");
		ssText << "FPS: " << fps;
		DrawLib->SetDrawColor(5, 171, 33);
		DrawLib->SetFont(G::DebugTextFont);
		DrawLib->DrawString(gmodSDK->info.w - (ssText.str().length() * 10), 5, ssText.str().c_str());
	}

	return (((EndSceneFn)dxHookManager->get_original(42)))(pDevice);
}

long __stdcall hkReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	return (((resetFn)dxHookManager->get_original(16)))(device, pPresentationParameters);
}

bool __stdcall hkCreateMove(float flInputSampleTime, CUserCmd * cmd)
{
	bool result = true;

	if (cmd == nullptr || !cmd->command_number)
		return result;

	if (G::Variables::AimbotEnabled)
	{
		result = Aimbot->CreateMove(cmd);
		oCreateMove(flInputSampleTime, cmd);
	}
	else result = oCreateMove(flInputSampleTime, cmd);
	
	return result;
}

HCURSOR hook()
{
	if (menuOpen)
	{
		unlockcursor();
		return false;
	}
	return lockcursor();
}