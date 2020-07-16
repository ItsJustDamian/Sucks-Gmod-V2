/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#pragma once
#include "../../MainHeader.h"
//};

class C_BaseEntity
{
public:
	int GetHealth();
	int GetMaxHealth();
	int GetFlags();
	int GetClassID();

	bool IsDead();
	bool IsAlive();
	
	QAngle GetOrigin();
	QAngle GetViewOffset();
	QAngle GetEyePos();

	bool PushEntity();
};