/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#include "Aimbot.h"

C_BaseEntity * CAimbot::GetClosestEnemy(C_BaseEntity * Localplayer, Vector viewAngles, float FOV)
{
	QAngle ViewAngles = QAngle(viewAngles.x, viewAngles.y, viewAngles.z);
	C_BaseEntity * returnEntity = nullptr;
	float bestDelta = FLT_MAX;

	for (size_t i = 1; i <= Interfaces->EngineClient->GetMaxClients(); i++)
	{
		C_BaseEntity * entity = (C_BaseEntity*)Interfaces->ClientEntityList->GetClientEntity(i);

		if (entity == nullptr)
			continue;

		if (entity == Localplayer)
			continue;

		if (!entity->IsAlive())
			continue;

		QAngle Angle = Utils::CalcAngle(Localplayer->GetEyePos(), entity->GetEyePos());
		float delta = (Angle - ViewAngles).Clamped().Length();

		if (delta < bestDelta && delta < FOV)
		{
			bestDelta = delta;
			returnEntity = entity;
		}
	}

	return returnEntity;
}

bool CAimbot::CreateMove(CUserCmd * cmd)
{
	/*if (!(GetAsyncKeyState(0x43)))
		return true;*/

	QAngle QViewAngles = QAngle(cmd->viewangles.x, cmd->viewangles.y, cmd->viewangles.z);
	C_BaseEntity * Localplayer = (C_BaseEntity*)Utils::GetLocalPlayer();
	C_BaseEntity * TargetEntity = GetClosestEnemy(Localplayer, cmd->viewangles, G::Variables::AimbotFOV);

	if (TargetEntity == nullptr)
		return true;

	QAngle aimAngle = Utils::CalcAngle(Localplayer->GetEyePos(), TargetEntity->GetEyePos());
	aimAngle.Clamp();

	if (aimAngle.IsNan())
		return true;

	//Smoothing
	if(G::Variables::AimbotSmoothingEnabled)
		aimAngle = QViewAngles + (aimAngle - QViewAngles) / G::Variables::AimbotSmoothing;

	cmd->viewangles.x = aimAngle.x;
	cmd->viewangles.y = aimAngle.y;

	return !G::Variables::AimbotSilent;
}
