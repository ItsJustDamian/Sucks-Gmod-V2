/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#pragma once
#include "../MainHeader.h"

#include "Classes/QAngle.h"
#include "Classes/Vector.h"

//struct CUST_VMatrix { float m[4][4]; inline float* operator[](int i) { return m[i]; } inline const float* operator[](int i) const { return m[i]; } };

namespace Utils
{
	extern bool				file_exists(char * file);
	extern bool				ScreenTransform(QAngle & in, QAngle & out);
	extern bool				WorldToScreen(QAngle & in, QAngle & out);

	extern float			Distance(QAngle pos1, QAngle pos2);
	extern float			Distance2D(QAngle pos1, QAngle pos2);

	extern void				VectorAngles(const QAngle & forward, QAngle & angles);
	extern void*			GetLocalPlayer();

	extern QAngle			CalcAngle(QAngle src, QAngle dst);
};