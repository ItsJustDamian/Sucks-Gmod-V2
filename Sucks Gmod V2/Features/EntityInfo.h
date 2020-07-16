/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#pragma once
#include "../MainHeader.h"

class CEntityInfo
{
public:
	C_BaseEntity * GetNearestEntity(C_BaseEntity * Localplayer, int & playerId);
	void DrawInfo();
};

inline CEntityInfo * EntityInfo;