/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#include "EntityInfo.h"

C_BaseEntity * CEntityInfo::GetNearestEntity(C_BaseEntity * Localplayer, int & playerId)
{
	float bestDistance = FLT_MAX;
	C_BaseEntity * ReturnEntity = nullptr;

	for (size_t i = 1; i <= Interfaces->EngineClient->GetMaxClients(); i++)
	{
		C_BaseEntity * entity = (C_BaseEntity*)Interfaces->ClientEntityList->GetClientEntity(i);

		if (entity == nullptr)
			continue;

		if (entity == Localplayer)
			continue;

		if (!entity->IsAlive())
			continue;

		float distance = Utils::Distance(Localplayer->GetOrigin(), entity->GetOrigin());

		if (distance < bestDistance)
		{
			bestDistance = distance;
			ReturnEntity = entity;
			playerId = i;
		}
	}

	return ReturnEntity;
}

void CEntityInfo::DrawInfo()
{
	static std::stringstream ss;

	C_BaseEntity * Localplayer = (C_BaseEntity*)Utils::GetLocalPlayer();
	int playerId = 0;
	C_BaseEntity * TargetEntity = GetNearestEntity(Localplayer, playerId);

	DrawLib->SetFont(G::EspTextFont[16]);
	DrawLib->SetDrawColor(255, 0, 0);

	if (TargetEntity == nullptr)
	{
		DrawLib->DrawString(5, 100, "No Entities found!");
		return;
	}

	DrawLib->SetDrawColor(255, 255, 255);

	playerInfo pInfo;
	Interfaces->EngineClient->GetPlayerInfo(playerId, &pInfo);

	static char nameBuf[150];
	sprintf(nameBuf, "Name: %s", pInfo.Name);
	DrawLib->DrawString(5, 100, nameBuf);

	ss.str("");
	ss << "Health: " << TargetEntity->GetHealth() << "/" << TargetEntity->GetMaxHealth();
	DrawLib->DrawString(5, 120, ss.str().c_str());

	ss.str("");
	ss << "Flags: " << TargetEntity->GetFlags();
	DrawLib->DrawString(5, 140, ss.str().c_str());

	ss.str("");
	ss << "Distance: " << (int)Utils::Distance(TargetEntity->GetOrigin(), Localplayer->GetOrigin());
	DrawLib->DrawString(5, 160, ss.str().c_str());

	ss.str("");
	ss << "Distance 2D: " << (int)Utils::Distance2D(TargetEntity->GetOrigin(), Localplayer->GetOrigin());
	DrawLib->DrawString(5, 180, ss.str().c_str());
}
