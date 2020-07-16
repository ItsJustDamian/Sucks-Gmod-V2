/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#include "Visuals.h"

std::stringstream ss;

void CVisuals::DrawEsp()
{
	C_BaseEntity * Localplayer = (C_BaseEntity*)Utils::GetLocalPlayer();

	for (int i = 1; i <= Interfaces->EngineClient->GetMaxClients(); i++)
	{
		C_BaseEntity * entity = (C_BaseEntity*)Interfaces->ClientEntityList->GetClientEntity(i);

		if (entity == nullptr)
			continue;

		if (entity == Localplayer)
			continue;

		if (entity->IsDead())
			continue;

		QAngle pos = entity->GetOrigin();
		QAngle EyePos = entity->GetEyePos();

		QAngle W2SPos, W2SEyePos;
		
		if (Utils::WorldToScreen(pos, W2SPos) && Utils::WorldToScreen(EyePos, W2SEyePos))
		{
			float Distance = Utils::Distance(entity->GetOrigin(), Localplayer->GetOrigin());

			int height = W2SPos.y - W2SEyePos.y;
			int width = height / 2.4f;

			int x = W2SPos.x - gmodSDK->info.x;
			int y = W2SPos.y - gmodSDK->info.y;

			playerInfo pInfo;
			Interfaces->EngineClient->GetPlayerInfo(i, &pInfo);

			DrawLib->SetDrawColor(G::Variables::boxColor[0] * 255, G::Variables::boxColor[1] * 255, G::Variables::boxColor[2] * 255);
			
			DrawLib->DrawBorderBox(x - (width / 2), y - height, width, height, 1);
			
			if(G::Variables::EspSnaplinesEnabled)
				DrawLib->DrawLine(gmodSDK->info.w / 2, gmodSDK->info.h, x, y, 2);

			bool draw = true;
			int distanceTextY = 16;

			if (Distance < 2000)
			{
				distanceTextY = 20;
				DrawLib->SetFont(G::EspTextFont[16]);
			}
			else if (Distance < 4000)
			{
				distanceTextY = 16;
				DrawLib->SetFont(G::EspTextFont[12]);
			}
			else if (Distance < 6000)
			{
				distanceTextY = 12;
				DrawLib->SetFont(G::EspTextFont[8]);
			}
			else
				draw = false;
			
			if (draw)
			{
				DrawLib->SetDrawColor(G::Variables::textColor[0] * 255, G::Variables::textColor[1] * 255, G::Variables::textColor[2] * 255);
				DrawLib->DrawString(x - (width / 2), y, (const char*)pInfo.Name);

				ss.str("");
				ss << "Health: " << entity->GetHealth() << "/" << entity->GetMaxHealth();
				DrawLib->DrawString(x + (width / 2) + 5, y - height, ss.str().c_str());

				ss.str("");
				ss << "Distance: " << (int)Distance;
				DrawLib->DrawString(x + (width /2) + 5, (y - height) + distanceTextY, ss.str().c_str());
			}
		}
	}
}