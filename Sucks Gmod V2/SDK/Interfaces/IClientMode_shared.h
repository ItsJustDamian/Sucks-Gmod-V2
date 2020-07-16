/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#pragma once
#include "IClientMode.h"
#include "../Classes/GameEventListener.h"

class ClientModeShared : public IClientMode, public CGameEventListener
{
	// IClientMode overrides.
public:
	ClientModeShared();
	virtual			~ClientModeShared();

	virtual void	Init();
	virtual void	InitViewport();
	virtual void	VGui_Shutdown();
	virtual void	Shutdown();

	virtual void	LevelInit(const char *newmap);
	virtual void	LevelShutdown(void);

	virtual void	Enable();
	virtual void	Disable();
	virtual void	Layout();

	virtual void	ReloadScheme(bool flushLowLevel);
	virtual void	OverrideView(void *pSetup);
	virtual bool	ShouldDrawDetailObjects();
	virtual bool	ShouldDrawEntity(void *pEnt);
	virtual bool	ShouldDrawLocalPlayer(void *pPlayer);
	virtual bool	ShouldDrawViewModel();
	virtual bool	ShouldDrawParticles();
	virtual bool	ShouldDrawCrosshair(void);
	virtual bool	ShouldBlackoutAroundHUD();
	virtual void* ShouldOverrideHeadtrackControl();
	virtual void	AdjustEngineViewport(int& x, int& y, int& width, int& height);
	virtual void	PreRender(void *pSetup);
	virtual void	PostRender();
	virtual void	PostRenderVGui();
	virtual void	ProcessInput(bool bActive);
	virtual bool	CreateMove(float flInputSampleTime, void *cmd);
	virtual void	Update();

	// Input
	virtual int		KeyInput(int down, void* keynum, const char *pszCurrentBinding);
	virtual int		HudElementKeyInput(int down, void* keynum, const char *pszCurrentBinding);
	virtual void	OverrideMouseInput(float *x, float *y);
	virtual void	StartMessageMode(int iMessageModeType);
	virtual void *GetMessagePanel();

	virtual void	ActivateInGameVGuiContext(void *pPanel);
	virtual void	DeactivateInGameVGuiContext();

	// The mode can choose to not draw fog
	virtual bool	ShouldDrawFog(void);

	virtual float	GetViewModelFOV(void);
	virtual void* GetViewport() { return (void*)0; }
	// Gets at the viewports vgui panel animation controller, if there is one...
	virtual void *GetViewportAnimationController()
	{
		return nullptr;
	}

	virtual void FireGameEvent(void *event);

	virtual bool CanRecordDemo(char *errorMsg, int length) const { return true; }

	virtual int HandleSpectatorKeyInput(int down, void* keynum, const char *pszCurrentBinding);

	virtual void	ComputeVguiResConditions(void *pkvConditions);

	//=============================================================================
	// HPE_BEGIN:
	// [menglish] Save server information shown to the client in a persistent place
	//=============================================================================

	virtual wchar_t* GetServerName() { return 0; }
	virtual void SetServerName(wchar_t* name) {};
	virtual wchar_t* GetMapName() { return 0; }
	virtual void SetMapName(wchar_t* name) {};

	//=============================================================================
	// HPE_END
	//=============================================================================

	virtual bool	DoPostScreenSpaceEffects(const void *pSetup);

	virtual void	DisplayReplayMessage(const char *pLocalizeName, float flDuration, bool bUrgent,
		const char *pSound, bool bDlg);

	virtual bool	IsInfoPanelAllowed() { return true; }
	virtual void	InfoPanelDisplayed() { }
	virtual bool	IsHTMLInfoPanelAllowed() { return true; }

protected:
	void			*m_pViewport;

	void			DisplayReplayReminder();

private:
	virtual void	UpdateReplayMessages();

	void			ClearReplayMessageList();

#if defined( REPLAY_ENABLED )
	float					m_flReplayStartRecordTime;
	float					m_flReplayStopRecordTime;
	CReplayReminderPanel	*m_pReplayReminderPanel;
#endif

	// Message mode handling
	// All modes share a common chat interface
	void			*m_pChatElement;
	void*			m_CursorNone;
	void *m_pWeaponSelection;
	int						m_nRootSize[2];
};