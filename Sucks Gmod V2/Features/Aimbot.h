/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#pragma once
#include "../MainHeader.h"

class C_BaseEntity;

class CAimbot
{
public:
	C_BaseEntity * GetClosestEnemy(C_BaseEntity * Localplayer, Vector viewAngles, float FOV);
	bool CreateMove(CUserCmd * cmd);
};

inline CAimbot * Aimbot;

