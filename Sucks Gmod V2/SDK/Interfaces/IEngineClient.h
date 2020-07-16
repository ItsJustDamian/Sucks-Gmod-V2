/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#pragma once
#include "../../MainHeader.h"
#include "../Classes/VMatrix.h"

struct playerInfo
{
	char* Name[32];
	char* random[0x666];
};

class IEngineClient
{
public:
	VMatrix GetViewMatrix();
	int GetMaxClients();
	void GetScreenSize(int & width, int & height);
	int GetLocalPlayer();
	bool GetPlayerInfo(int id, playerInfo* plrinfo);
};